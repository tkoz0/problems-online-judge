#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <map>

int main(int argc, char **argv)
{
    std::map<std::string,uint32_t> trees;
    uint32_t cases;
    std::cin >> cases;
    std::string line;
    std::getline(std::cin,line); // skip to first test case
    std::getline(std::cin,line);
    while (cases--)
    {
        trees.clear();
        uint32_t num_trees = 0;
        while (std::getline(std::cin,line))
        {
            if (line == std::string("")) break; // end of test case
            ++trees[line];
            ++num_trees;
        }
        assert(num_trees);
        for (auto itr : trees)
            printf("%s %.4lf\n",itr.first.c_str(), // print percent
                   100.0*(double)(itr.second)/(double)(num_trees));
        if (cases) printf("\n"); // no extra line at end
    }
    return 0;
}
