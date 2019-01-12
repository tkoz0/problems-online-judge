#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <sstream>
#include <iostream>
#include <list>

int main(int argc, char **argv)
{
    int64_t x;
    while (std::cin >> x)
    {
        std::cin.ignore(); // skip new line
        std::string line;
        std::getline(std::cin,line);
        std::stringstream ss(line); // extract c constants
        std::list<int64_t> c;
        int64_t t;
        while (ss >> t) c.push_front(t);
        int64_t sum = 0;
        auto itr = c.begin();
        ++itr; // skip constant that goes to 0 with derivative
        int64_t i = 1;
        int64_t pow = 1; // sum terms
        for (; (uint32_t)(i) < c.size(); ++i, ++itr, pow *= x)
            sum += i*(*itr)*pow;
        printf("%li\n",sum);
    }
    return 0;
}
