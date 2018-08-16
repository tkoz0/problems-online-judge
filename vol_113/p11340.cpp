#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
typedef uint32_t u32;
typedef uint8_t u8;

u32 pay[256];

int main(int argc, char **argv)
{
    u32 N, K, p, M, paid;
    u8 ch;
    std::string line;
    std::cin >> N;
//    assert(N and N <= 5);
    while (N--)
    {
        for (u32 i = 0; i < 256; ++i) pay[i] = 0;
        std::cin >> K;
//        assert(K and K <= 100);
//        std::unordered_map<char,u32> pay;
        while (K--)
        {
            std::cin >> ch >> p;
            pay[ch] = p;
//            printf("map %c to %u\n",ch,p);
        }
        std::cin >> M;
//        assert(M and M <= 150000);
        std::getline(std::cin,line); // finish off line with M on it
        paid = 0;
        while (M--)
        {
            std::getline(std::cin,line);
//            printf("line %s\n",line.c_str());
            for (auto itr = line.begin(); itr != line.end(); ++itr)
            {
                ch = *itr;
                paid += pay[ch];
//                auto itr2 = pay.find(*itr);
//                if (itr2 != pay.end()) paid += itr2->second;
            }
        }
        printf("%u.%02u$\n",paid/100,paid%100);
    }
    return 0;
}
