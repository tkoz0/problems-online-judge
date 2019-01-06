#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <iostream>

std::string extract_title(const std::string& s)
{
    uint32_t i = 0;
    while (s[i] != '\"') ++i;
    uint32_t j = i+1;
    while (s[j] != '\"') ++j;
    return s.substr(i+1,j-i-1);
}

int main(int argc, char **argv)
{
    std::string line, author, title;
    std::map<std::string,std::set<std::string> > shelf;
    // map author --> sorted titles for correct sorting order
    std::unordered_map<std::string,std::string> author_of; // title --> author
    while (std::getline(std::cin,line)) // read books to build shelf
    {
        if (line == std::string("END")) break;
        title = extract_title(line);
        uint32_t i = 1; // find 2nd "
        while (line[i] != '\"') ++i;
        assert(line.substr(i+1,4) == std::string(" by "));
        author = line.substr(i+5);
        shelf[author].insert(title); // insert into shelf
        author_of[title] = author;
    }
    std::map<std::string,std::set<std::string> > borrowed, returned;
    while (std::cin >> line)
    {
        if (line == std::string("END")) break;
        else if (line == std::string("BORROW"))
        {
            std::getline(std::cin,line);
            title = extract_title(line);
            auto itr1 = shelf.find(author_of[title]); // locate book
            assert(itr1 != shelf.end());
            auto itr2 = itr1->second.find(title);
            assert(itr2 != itr1->second.end());
            borrowed[author_of[title]].insert(title); // perform borrow
            itr1->second.erase(itr2); // remove from shelf
        }
        else if (line == std::string("RETURN"))
        {
            std::getline(std::cin,line);
            title = extract_title(line);
            auto itr1 = borrowed.find(author_of[title]); // locate book
            assert(itr1 != borrowed.end());
            auto itr2 = itr1->second.find(title);
            assert(itr2 != itr1->second.end());
            returned[author_of[title]].insert(title); // perform return
            itr1->second.erase(itr2); // no longer borrowed
        }
        else if (line == std::string("SHELVE"))
        {
            // loop over returned and place them back on shelf
            for (auto author_itr : returned)
            {
                for (auto title_itr : author_itr.second)
                {
                    shelf[author_itr.first].insert(title_itr); // reshelf
                    // find in shelf and locate book before it
                    auto s_auth = shelf.find(author_itr.first);
                    assert(s_auth != shelf.end());
                    auto s_titl = s_auth->second.find(title_itr);
                    assert(s_titl != s_auth->second.end());
                    if (s_titl != s_auth->second.begin())
                    {
                        // decrement it and use that book
                        --s_titl;
                        printf("Put \"%s\" after \"%s\"\n",title_itr.c_str(),
                                s_titl->c_str());
                    }
                    else
                    {
                        // decrement s_auth and pick last
                        bool found = false;
                        for (;;)
                        {
                            if (s_auth == shelf.begin()) break; // no more
                            --s_auth; // see if there is a last book here
                            if (s_auth->second.size())
                            {
                                found = true;
                                s_titl = s_auth->second.end();
                                --s_titl;
                                break;
                            }
                        }
                        if (found)
                            printf("Put \"%s\" after \"%s\"\n",
                                    title_itr.c_str(),
                                    s_titl->c_str());
                        else printf("Put \"%s\" first\n",title_itr.c_str());
                    }
                }
            }
            returned.clear();
            printf("END\n");
        }
        else assert(0);
    }
    return 0;
}
