#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include <iostream>
#include <map>
#include <string>

#define DLIM 10.0F
#define GLIM 1000.0F
#define SMIN 1
#define SMAX 32767
#define NMAX 100
#define SWEEP_TIME 5.0F
#define TOLERANCE 0.1F
#define PI 3.1415926F
typedef uint32_t u32;

// warning messages
#define EW " -- equipment warning"
#define NI " -- new intrusion"
#define NA " -- new aloft"
#define DE " -- domain exited"
#define DL " -- domain loss"

struct pos
{
    float A, D, G;
    // A = asimuth, angle like clock, 12 is north
    // D = distance, radar to plane
    // G = ground speed
};

// converts to x,y and uses distance formula
float polar_distance(float r1, float a1, float r2, float a2)
{
    // conversion of coordinate systems is unnecessary since the original is
    // a same size rotation and angular reflection of standard polar system
    float dx = r1*cos(a1*PI/180.0F) - r2*cos(a2*PI/180.0F);
    float dy = r1*sin(a1*PI/180.0F) - r2*sin(a2*PI/180.0F);
//    printf("dx = %f, dy = %f\n",dx,dy);
    return sqrt(dx*dx + dy*dy);
}

void print_warnings(const std::map<std::string, pos>& s1,
                    const std::map<std::string, pos>& s2)
{
    auto itr1 = s1.begin(), itr2 = s2.begin();
    while (itr1 != s1.end()) // loop until s1 finishes
    {
        if (itr2 == s2.end()) // remaining in s1 not in s2
        {
            for (; itr1 != s1.end(); ++itr1)
            {
                float maxdist = (itr1->second.G * (1.0F + TOLERANCE))
                        * (SWEEP_TIME/3600.0F);
                if (DLIM - itr1->second.D < maxdist)
                    printf("%5s%s\n", itr1->first.c_str(), DE);
                else printf("%5s%s\n", itr1->first.c_str(), DL);
            }
            break;
        }
        assert(itr1 != s1.end() and itr2 != s2.end());
        if (itr1->first == itr2->first) // ids match
        {
            // average reported speed, calculated speed from positions
            float avgspeed = (itr1->second.G + itr2->second.G) / 2.0F;
            float calcspeed = polar_distance(itr1->second.D, itr1->second.A,
                    itr2->second.D, itr2->second.A) * (3600.0F/SWEEP_TIME);
//            printf("avg = %f, calc = %f\n",avgspeed,calcspeed);
            if (fabs(avgspeed - calcspeed) > TOLERANCE * calcspeed)
                printf("%5s%s\n", itr1->first.c_str(), EW);
            ++itr1, ++itr2;
        }
        else if (itr1->first < itr2->first) // search s1
            for (; itr1 != s1.end() and itr1->first < itr2->first; ++itr1)
            {
                float maxdist = (itr1->second.G * (1.0F + TOLERANCE))
                        * (SWEEP_TIME/3600.0F);
                if (DLIM - itr1->second.D < maxdist)
                    printf("%5s%s\n", itr1->first.c_str(), DE);
                else printf("%5s%s\n", itr1->first.c_str(), DL);
            }
        else // search s2
        {
            assert(itr2->first < itr1->first);
            for (; itr2 != s2.end() and itr2->first < itr1->first; ++itr2)
            {
                float maxdist = (itr2->second.G * (1.0F + TOLERANCE))
                        * (SWEEP_TIME/3600.0F);
                if (DLIM - itr2->second.D < maxdist)
                    printf("%5s%s\n", itr2->first.c_str(), NI);
                else printf("%5s%s\n", itr2->first.c_str(), NA);
            }
        }
    }
    for (; itr2 != s2.end(); ++itr2) // finish planes in s2 (if needed)
    {
        float maxdist = (itr2->second.G * (1.0F + TOLERANCE))
                * (SWEEP_TIME/3600.0F);
        if (DLIM - itr2->second.D < maxdist)
            printf("%5s%s\n", itr2->first.c_str(), NI);
        else printf("%5s%s\n", itr2->first.c_str(), NA);
    }
}

int main(int argc, char **argv)
{
    u32 N1, N2, scenario = 0;
    int r;
    std::map<std::string, pos> s1, s2;
    std::string S;
    pos p;
    while (++scenario, scanf("%u", &N1) == 1)
    {
        assert(N1 <= NMAX);
        s1.clear();
        s2.clear();
        while (N1--) // radar sweep 1
        {
            std::cin >> S;
            r = scanf("%f %f %f", &p.A, &p.D, &p.G);
            assert(r == 3);
//            assert(SMIN <= S and S < SMAX);
            assert(S.length() <= 5);
            assert(0.0 <= p.A and p.A < 360.0F);
            assert(0.0 <= p.D and p.D <= DLIM);
            assert(0.0 <= p.G and p.G < GLIM);
            s1[S] = p;
        }
        r = scanf("%u", &N2);
        assert(r == 1);
        assert(N2 <= NMAX);
        while (N2--) // radar sweep 2
        {
            std::cin >> S;
            r = scanf("%f %f %f", &p.A, &p.D, &p.G);
            assert(r == 3);
//            assert(SMIN <= S and S < SMAX);
            assert(S.length() <= 5);
            assert(0.0 <= p.A and p.A < 360.0F);
            assert(0.0 <= p.D and p.D <= DLIM);
            assert(0.0 <= p.G and p.G < GLIM);
            s2[S] = p;
        }
        printf("Scenario # %u\n", scenario);
        print_warnings(s1, s2);
        printf("\n");
    }
    return 0;
}
