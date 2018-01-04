#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include <iostream>
#include <string>

// read line by line, using an alternating boolean to determine if the text
// is quoted in tex
int main(int argc, char **argv)
{
    std::string line, output;
    bool quoted = false;
    while (std::cin)
    {
        std::getline(std::cin, line);
        if (not std::cin) break; // reached EOF
        output = "";
        for (auto i = line.begin(); i != line.end(); ++i)
        {
            if (*i == '"')
            {
                if (quoted) output += "''";
                else output += "``";
                quoted = !quoted;
            }
            else output += *i;
        }
        std::cout << output << std::endl;
    }
    return 0;
}
