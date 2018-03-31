#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include <map>
#include <string>

typedef uint32_t u32;

#define MAX_PLANES 100
#define RADIUS 10.0
#define TIME_SEC 5.0
#define TIME_HR (TIME_SEC / 3600.0)
#define TOLERANCE 0.10
#define SPEED_LIM 1000.0
#define PI 3.14159265358979323846
#define RADIANS(x) (x * PI / 180.0)

// warning messages
#define EW " -- equipment warning"
#define NI " -- new intrusion"
#define NA " -- new aloft"
#define DE " -- domain exited"
#define DL " -- domain loss"

struct pos { double a, d, g; }; // angle, distance, ground speed

#include <iostream>

std::ostream& operator<<(std::ostream& o, const pos p)
{
    o << "(" << p.a << "," << p.d << "," << p.g << ")";
    return o;
}

// equipment warning: avg reported speed >10% off from calculated speed
inline bool same_plane_ew(pos p1, pos p2)
{
    double dx = p2.d * cos(RADIANS(p2.a)) - p1.d * cos(RADIANS(p1.a));
    double dy = p2.d * sin(RADIANS(p2.a)) - p1.d * sin(RADIANS(p1.a));
    double calcspeed = sqrt(dx * dx + dy * dy) / TIME_HR;
    double avgreported = (p1.g + p2.g) / 2.0;
    return fabsl(avgreported - calcspeed) > (TOLERANCE * avgreported);
//    std::cout<<p1<<p2<<b<<",calc="<<calcspeed<<",avg="<<avgreported<<std::endl;
}

// its speed+10% is sufficient to cover distance between position and the edge
inline bool speed_to_edge_sufficient(pos p)
{
    double from_edge = RADIUS - p.d;
    double max_dist = (p.g * (1.0 + TOLERANCE)) * TIME_HR;
    return from_edge <= max_dist;
}

char* scan_str() // reads consecutive string without whitespace
{
    char c;
    while (scanf("%c", &c) == 1)
        if (c != ' ' and c != '\n')
            goto scan_str_start;
    return NULL; // reach EOF
    scan_str_start:
    size_t l = 2, i = 0;
    char *str = (char*) malloc(sizeof(char) * l);
    assert(str);
    str[i++] = c;
    while (scanf("%c", &c) == 1) // read chars and reallocate
    {
        if (c == ' ' or c == '\n') break;
        str[i++] = c;
        str = (char*) realloc(str, sizeof(char) * (++l));
    }
    str[i] = '\0'; // null terminate
    return str;
}

inline u32 str_to_u32(char *str) // interprets string as integer
{
    assert(str);
    u32 i = 0;
    while (*str) i *= 10, i += *str - '0', ++str;
    return i;
}

void print_warnings(const std::map<u32, std::pair<std::string, pos> >& s1,
                    const std::map<u32, std::pair<std::string, pos> >& s2)
{
//    printf("pw_s1:");for(auto u:s1)printf(" %s",u.second.first.c_str());printf("\n");
//    printf("pw_s2:");for(auto u:s2)printf(" %s",u.second.first.c_str());printf("\n");
    auto itr1 = s1.begin(), itr2 = s2.begin();
    while (itr1 != s1.end()) // loop to s1 end
    {
        if (itr2 == s2.end()) // finish s1 (disappeared planes)
        {
            for (; itr1 != s1.end(); ++itr1)
            {
                if (speed_to_edge_sufficient(itr1->second.second))
                    printf("%5s%s\n", itr1->second.first.c_str(), DE);
                else printf("%5s%s\n", itr1->second.first.c_str(), DL);
            }
            break;
        }
        assert(itr1 != s1.end());
        if (itr1->first < itr2->first) // s1<s2 --> iterate s1 forward
        {
            if (speed_to_edge_sufficient(itr1->second.second))
                printf("%5s%s\n", itr1->second.first.c_str(), DE);
            else printf("%5s%s\n", itr1->second.first.c_str(), DL);
            ++itr1;
        }
        else if (itr1->first > itr2->first) // s1>s2 --> iterate s2 forward
        {
            if (speed_to_edge_sufficient(itr2->second.second))
                printf("%5s%s\n", itr2->second.first.c_str(), NI);
            else printf("%5s%s\n", itr2->second.first.c_str(), NA);
            ++itr2;
        }
        else // same, check for equipment warning
        {
            assert(itr1->first == itr2->first);
            if (same_plane_ew(itr1->second.second, itr2->second.second))
                printf("%5s%s\n", itr1->second.first.c_str(), EW);
            ++itr1, ++itr2;
        }
    }
    for (; itr2 != s2.end(); ++itr2) // finish s2 (newly appeared planes)
    {
        if (speed_to_edge_sufficient(itr2->second.second))
            printf("%5s%s\n", itr2->second.first.c_str(), NI);
        else printf("%5s%s\n", itr2->second.first.c_str(), NA);
    }
}

int main(int argc, char **argv)
{
    u32 scenario = 0, N;
    std::map<u32, std::pair<std::string, pos> > s1, s2;
    pos p;
    char *str;
    int r;
//    char *z;while ((z=scan_str())){printf("%s\n",z);free(z);}return 0;
    while (++scenario, scanf("%u", &N) == 1) // next scenario
    {
        assert(N <= MAX_PLANES);
        s1.clear();
        while (N--) // read sweep 1
        {
            str = scan_str();
            assert(str);
            r = scanf("%lf %lf %lf", &p.a, &p.d, &p.g);
            assert(r == 3);
            assert(0.0 <= p.a and p.a < 360.0);
            assert(0.0 <= p.d and p.d <= RADIUS);
            assert(0.0 <= p.g and p.g < SPEED_LIM);
            s1[str_to_u32(str)] = std::make_pair(std::string(str), p);
            free(str);
        }
        r = scanf("%u", &N);
        assert(r == 1);
        assert(N <= MAX_PLANES);
        s2.clear();
        while (N--) // read sweep 2
        {
            str = scan_str();
            assert(str);
            r = scanf("%lf %lf %lf", &p.a, &p.d, &p.g);
            assert(r == 3);
            assert(0.0 <= p.a and p.a < 360.0);
            assert(0.0 <= p.d and p.d <= RADIUS);
            assert(0.0 <= p.g and p.g < SPEED_LIM);
            s2[str_to_u32(str)] = std::make_pair(std::string(str), p);
            free(str);
        }
        printf("Scenario # %u\n", scenario);
        print_warnings(s1, s2);
        printf("\n");
    }
    return 0;
}
