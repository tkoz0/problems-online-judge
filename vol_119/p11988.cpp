#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <list>

int main(int argc, char **argv)
{
    std::string line;
    while (std::getline(std::cin,line)) // for each test case (1 per line)
    {
        auto itr1 = line.begin();
        std::list<std::string> beiju; // linked list for fast push_front
        bool ins_end = true; // insertion point
        for (;;)
        {
            auto itr2 = itr1; // find next []
            while (itr2 != line.end() and *itr2 != '[' and *itr2 != ']') ++itr2;
            std::string s = std::string(itr1,itr2); // between [] chars
            if (!s.empty()) // insert to list if nonempty
            {
                if (ins_end) beiju.push_back(s);
                else beiju.push_front(s);
            }
            if (itr2 == line.end()) break; // end of input
            ins_end = (*itr2 == ']');
            itr1 = itr2+1;
        }
        for (auto s : beiju) // print linked list of strings
            printf("%s",s.c_str());
        printf("\n");
    }
    return 0;
}
