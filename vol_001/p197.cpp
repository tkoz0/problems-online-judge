#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
typedef uint32_t u32;
typedef std::vector<std::vector<std::vector<char> > > char3d;
typedef std::vector<std::vector<char> > char2d;
typedef std::vector<char> char1d;

// find all possibilities considering one orientation of block "a"
// to get all the others, rotate the solutions found and identify the solutions
// set based on the orientation of block "a"
// output the appropriate solution set when given user input

struct CUBE
{
    u32 X, Y, Z; // dimensions
    std::vector<std::vector<std::vector<char> > > cube;
    // removed constructor so that 3d vector initializer lists work
};

CUBE new_cube(u32 X, u32 Y, u32 Z)
{
    return {X,Y,Z,std::vector<std::vector<std::vector<char> > >(X,
                   std::vector<std::vector<char> >(Y,
                    std::vector<char>(Z,'.'))) };
}

std::string encode(CUBE& cube) // cube --> 27 char string
{
    assert(cube.X == 3 and cube.Y == 3 and cube.Z == 3);
    std::string s = "";
    for (u32 x = 0; x < 3; ++x)
        for (u32 y = 0; y < 3; ++y)
            for (u32 z = 0; z < 3; ++z)
                s.push_back(cube.cube[x][y][z]);
    return s;
}

CUBE decode(std::string& s) // 27 char string --> cube
{
    assert(s.length() == 27);
    CUBE cube = new_cube(3,3,3);
    for (u32 x = 0; x < 3; ++x)
        for (u32 y = 0; y < 3; ++y)
            for (u32 z = 0; z < 3; ++z)
                cube.cube[x][y][z] = s[9*x+3*y+z];
    return cube;
}

// orientation of 7 pieces as given
CUBE A0 = {2,1,3,{{{'a','a','a'}},{{'.','.','a'}}}};
CUBE B0 = {1,2,2,{{{'b','b'},{'b','.'}}}};
CUBE C0 = {2,1,3,{{{'.','c','.'}},{{'c','c','c'}}}};
CUBE D0 = {1,3,2,{{{'d','.'},{'d','d'},{'.','d'}}}};
CUBE E0 = {2,2,2,{{{'e','e'},{'.','e'}},{{'.','e'},{'.','.'}}}};
CUBE F0 = {2,2,2,{{{'e','e'},{'.','e'}},{{'.','e'},{'.','.'}}}};
CUBE G0 = {2,2,2,{{{'.','.'},{'g','g'}},{{'.','g'},{'.','g'}}}};

// rotation functions for 2d arrays
std::vector<std::vector<char> > rot0(std::vector<std::vector<char> >& flat)
{
    auto rot = std::vector<std::vector<char> >(flat.size(),
                             std::vector<char>('.',flat[0].size()));
    for (u32 x = 0; x < flat.size(); ++x)
        for (u32 y = 0; y < flat[0].size(); ++y)
            rot[x][y] = flat[x][y];
    return rot;
}
std::vector<std::vector<char> > rot90(std::vector<std::vector<char> >& flat)
{
    auto rot = std::vector<std::vector<char> >(flat.size(),
                             std::vector<char>('.',flat[0].size()));
    for (u32 x = 0; x < flat[0].size(); ++x)
        for (u32 y = 0; y < flat.size(); ++y)
            rot[x][y] = flat[y][flat[0].size()-1-x];
    return rot;
}
std::vector<std::vector<char> > rot180(std::vector<std::vector<char> >& flat)
{
    auto rot = std::vector<std::vector<char> >(flat.size(),
                             std::vector<char>('.',flat[0].size()));
    for (u32 x = 0; x < flat.size(); ++x)
        for (u32 y = 0; y < flat[0].size(); ++y)
            rot[x][y] = flat[flat.size()-1-x][flat[0].size()-1-y];
    return rot;
}
std::vector<std::vector<char> > rot270(std::vector<std::vector<char> >& flat)
{
    auto rot = std::vector<std::vector<char> >(flat.size(),
                             std::vector<char>('.',flat[0].size()));
    for (u32 x = 0; x < flat[0].size(); ++x)
        for (u32 y = 0; y < flat.size(); ++y)
            rot[x][y] = flat[flat.size()-1-y][x];
    return rot;
}
std::vector<CUBE> all_rots(CUBE& cube) // get all rotations of a 2d array
{
    std::vector<CUBE> results;
    CUBE cube1(cube);
    for (u32 x = 0; x < cube1.X; ++x) cube1.cube[x] = rot0(cube1.cube[x]);
    CUBE cube2(cube);
    for (u32 x = 0; x < cube2.X; ++x) cube2.cube[x] = rot90(cube2.cube[x]);
    CUBE cube3(cube);
    for (u32 x = 0; x < cube3.X; ++x) cube3.cube[x] = rot180(cube3.cube[x]);
    CUBE cube4(cube);
    for (u32 x = 0; x < cube4.X; ++x) cube4.cube[x] = rot270(cube4.cube[x]);
    results.push_back(cube1);
    results.push_back(cube2);
    results.push_back(cube3);
    results.push_back(cube4);
    return results;
}

std::vector<CUBE> compute_rotations(CUBE& cube) // get all 24 rotations
{
    u32 X = cube.cube.size();
    u32 Y = cube.cube[0].size();
    u32 Z = cube.cube[0][0].size();
    // TODO
}

void initialize_blocks() // generate block orientation data
{
    ;
}

void _validate_cube_input(std::string& s) // input should only have "a" block
{
    for (char c : s)
        assert(c == '.' or c == 'a');
}

std::vector<CUBE> initial_solutions;

void find_solutions_a()
{
    ;
}

int main(int argc, char **argv)
{
    initialize_blocks();
    // compute all solutions with an initial configuration of the "a" piece
    std::string initial = "aaaa.......................";
    CUBE cube = decode(initial);
    initial_solutions.clear();
    find_solutions_a();
    // hard coded check for number of solutions, believed to be 480
    assert(initial_solutions.size() == 480);
    // TODO compute all rotations for solutions
    // process input
    std::string line;
    while (std::getline(std::cin,line)) // based on "a" position, get solutions
    {
        _validate_cube_input(line);
        // TODO determine orientation of "a" block, use to get solutions
    }
    return 0;
}
