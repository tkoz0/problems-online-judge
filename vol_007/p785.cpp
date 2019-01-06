#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <set>

bool is_end_line(const std::string& s)
{
    for (char c : s) if (c != '_') return false;
    return !s.empty();
}

int main(int argc, char **argv)
{
    for (;;)
    {
        std::vector<std::string> grid;
        std::string end_line, line;
        for (;;)
        {
            if (!std::getline(std::cin,line)) goto end; // EOF
            if (is_end_line(line))
            {
                end_line = line;
                break;
            }
            grid.push_back(line);
        }
        std::vector<std::vector<bool> > marked;
        for (auto r : grid) // generate
            marked.push_back(std::vector<bool>(r.length(),false));
        // find contour char
        char contour = '\0';
        for (auto r : grid)
            for (auto c : r)
                if (c != '_' and c != ' ')
                {
                    contour = c;
                    goto done1;
                }
        done1:
        assert(contour != '\0'); // contour was found
        // region filling loop
        for (size_t r = 0; r != marked.size(); ++r)
            for (size_t c = 0; c != marked[r].size(); ++c)
            {
                if (marked[r][c]) continue; // was part of previous region
                if (grid[r][c] == contour) continue; // not inside region
                std::stack<std::pair<size_t,size_t> > stack;
                stack.push(std::make_pair(r,c)); // for iterative flood fill
                char marking_char = '\0';
                std::set<std::pair<size_t,size_t> > region; // points inside
                while (!stack.empty())
                {
                    std::pair<size_t,size_t> loc = stack.top();
                    stack.pop();
                    if (loc.first >= marked.size() // bounds check
                        or loc.second >= marked[loc.first].size()) continue;
                    if (grid[loc.first][loc.second] == contour) continue;
                    if (marked[loc.first][loc.second]) continue;
                    if (grid[loc.first][loc.second] != ' ') // marking char
                    {
                        if (marking_char == '\0') // first instance
                            marking_char = grid[loc.first][loc.second];
                        else assert(grid[loc.first][loc.second]
                                    == marking_char); // should be same
                    }
                    marked[loc.first][loc.second] = true;
                    region.insert(loc);
                    // DFS to adjacent cells
                    stack.push(std::make_pair(loc.first+1,loc.second));
                    stack.push(std::make_pair(loc.first,loc.second+1));
                    stack.push(std::make_pair(loc.first-1,loc.second));
                    stack.push(std::make_pair(loc.first,loc.second-1));
                }
                if (marking_char != '\0') // fill region
                    for (auto loc : region)
                        grid[loc.first][loc.second] = marking_char;
            }
        // print results
        for (auto r : grid) printf("%s\n",r.c_str());
        printf("%s\n",end_line.c_str());
    }
    end:
    return 0;
}
