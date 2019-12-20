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

// create cube and get dimensions
u32 xlen(char3d& c) { return c.size(); }
u32 ylen(char3d& c) { return c[0].size(); }
u32 zlen(char3d& c) { return c[0][0].size(); }
char3d new_cube(u32 X, u32 Y, u32 Z)
{
    return char3d(X,char2d(Y,char1d(Z,'.')));
}

std::string encode(char3d& cube) // cube --> 27 char string
{
    assert(xlen(cube) == 3 and ylen(cube) == 3 and zlen(cube) == 3);
    std::string s = "";
    for (u32 x = 0; x < 3; ++x)
        for (u32 y = 0; y < 3; ++y)
            for (u32 z = 0; z < 3; ++z)
                s.push_back(cube[x][y][z]);
    return s;
}

char3d decode(std::string& s) // 27 char string --> cube
{
    assert(s.length() == 27);
    char3d cube = new_cube(3,3,3);
    for (u32 x = 0; x < 3; ++x)
        for (u32 y = 0; y < 3; ++y)
            for (u32 z = 0; z < 3; ++z)
                cube[x][y][z] = s[9*x+3*y+z];
    return cube;
}

// orientation of 7 pieces as given
char3d A0 = {{{'a','a','a'}},{{'.','.','a'}}};
char3d B0 = {{{'b','b'},{'b','.'}}};
char3d C0 = {{{'.','c','.'}},{{'c','c','c'}}};
char3d D0 = {{{'d','.'},{'d','d'},{'.','d'}}};
char3d E0 = {{{'e','e'},{'.','e'}},{{'.','e'},{'.','.'}}};
char3d F0 = {{{'.','.'},{'.','f'}},{{'f','f'},{'.','f'}}};
char3d G0 = {{{'.','.'},{'g','g'}},{{'.','g'},{'.','g'}}};
std::vector<char3d> A, B, C, D, E, F, G; // for all possible orientations

// rotation functions for 2d arrays
char2d rot0(char2d& flat)
{
    auto rot = char2d(flat.size(),char1d('.',flat[0].size()));
    for (u32 x = 0; x < flat.size(); ++x)
        for (u32 y = 0; y < flat[0].size(); ++y)
            rot[x][y] = flat[x][y];
    return rot;
}
char2d rot90(char2d& flat)
{
    auto rot = char2d(flat[0].size(),char1d('.',flat.size()));
    for (u32 x = 0; x < flat[0].size(); ++x)
        for (u32 y = 0; y < flat.size(); ++y)
            rot[x][y] = flat[y][flat[0].size()-1-x];
    return rot;
}
char2d rot180(char2d& flat)
{
    auto rot = char2d(flat.size(),char1d('.',flat[0].size()));
    for (u32 x = 0; x < flat.size(); ++x)
        for (u32 y = 0; y < flat[0].size(); ++y)
            rot[x][y] = flat[flat.size()-1-x][flat[0].size()-1-y];
    return rot;
}
char2d rot270(char2d& flat)
{
    auto rot = char2d(flat[0].size(),char1d('.',flat.size()));
    for (u32 x = 0; x < flat[0].size(); ++x)
        for (u32 y = 0; y < flat.size(); ++y)
            rot[x][y] = flat[flat.size()-1-y][x];
    return rot;
}
std::vector<char3d> all_rots(char3d& cube) // rotate around x axis
{
    std::vector<char3d> results;
    char3d cube1 = char3d(xlen(cube));
    for (u32 x = 0; x < xlen(cube1); ++x) cube1[x] = rot0(cube[x]);
    char3d cube2 = char3d(xlen(cube));
    for (u32 x = 0; x < xlen(cube2); ++x) cube2[x] = rot90(cube[x]);
    char3d cube3 = char3d(xlen(cube));
    for (u32 x = 0; x < xlen(cube3); ++x) cube3[x] = rot180(cube[x]);
    char3d cube4 = char3d(xlen(cube));
    for (u32 x = 0; x < xlen(cube4); ++x) cube4[x] = rot270(cube[x]);
    results.push_back(cube1);
    results.push_back(cube2);
    results.push_back(cube3);
    results.push_back(cube4);
    return results;
}

std::vector<char3d> compute_rotations(char3d& cube) // get all 24 rotations
{
    u32 X = xlen(cube);
    u32 Y = ylen(cube);
    u32 Z = zlen(cube);
    u32 x, y, z;
    std::vector<char3d> results = all_rots(cube);
    char3d cube2 = new_cube(Y,Z,X); // initialize cube rotations
    char3d cube3 = new_cube(Z,X,Y);
    char3d cube4 = new_cube(Z,Y,X);
    char3d cube5 = new_cube(Y,X,Z);
    char3d cube6 = new_cube(X,Z,Y);
    for (x = 0; x < Y; ++x) // rotate cube
        for (y = 0; y < Z; ++y)
            for (z = 0; z < X; ++z)
                cube2[x][y][z] = cube[z][x][y];
    for (x = 0; x < Z; ++x)
        for (y = 0; y < X; ++y)
            for (z = 0; z < Y; ++z)
                cube3[x][y][z] = cube[y][z][x];
    for (x = 0; x < Z; ++x)
        for (y = 0; y < Y; ++y)
            for (z = 0; z < X; ++z)
                cube4[x][y][z] = cube[X-1-z][Y-1-y][Z-1-x];
    for (x = 0; x < Y; ++x)
        for (y = 0; y < X; ++y)
            for (z = 0; z < Z; ++z)
                cube5[x][y][z] = cube[X-1-y][Y-1-x][Z-1-z];
    for (x = 0; x < X; ++x)
        for (y = 0; y < Z; ++y)
            for (z = 0; z < Y; ++z)
                cube6[x][y][z] = cube[X-1-x][Y-1-z][Z-1-y];
    std::vector<char3d> rot2 = all_rots(cube2); // generate rotations
    std::vector<char3d> rot3 = all_rots(cube3);
    std::vector<char3d> rot4 = all_rots(cube4);
    std::vector<char3d> rot5 = all_rots(cube5);
    std::vector<char3d> rot6 = all_rots(cube6);
    results.insert(results.end(),rot2.begin(),rot2.end()); // combine results
    results.insert(results.end(),rot3.begin(),rot3.end());
    results.insert(results.end(),rot4.begin(),rot4.end());
    results.insert(results.end(),rot5.begin(),rot5.end());
    results.insert(results.end(),rot6.begin(),rot6.end());
    return results;
}

std::vector<char3d> dedup(std::vector<char3d>& l)
{
    auto l2 = std::vector<char3d>();
    for (char3d cube : l)
    {
        bool in_l2 = false;
        for (char3d cube2 : l2)
            if (cube == cube2)
            {
                in_l2 = true;
                break;
            }
        if (not in_l2) l2.push_back(cube);
    }
    return l2;
}

void initialize_blocks() // generate block orientation data
{
    std::vector<char3d> rotA, rotB, rotC, rotD, rotE, rotF, rotG;
    rotA = compute_rotations(A0);
    rotB = compute_rotations(B0);
    rotC = compute_rotations(C0);
    rotD = compute_rotations(D0);
    rotE = compute_rotations(E0);
    rotF = compute_rotations(F0);
    rotG = compute_rotations(G0);
    A = dedup(rotA);
    B = dedup(rotB);
    C = dedup(rotC);
    D = dedup(rotD);
    E = dedup(rotE);
    F = dedup(rotF);
    G = dedup(rotG);
}

void _validate_cube_input(std::string& s) // input should only have "a" block
{
    for (char c : s)
        assert(c == '.' or c == 'a');
}

std::vector<char3d> initial_solutions;
char3d rec_cube;

void find_solutions_a()
{
    printf("%lu %lu %lu %lu %lu %lu %lu\n",A.size(),B.size(),C.size(),
                                    D.size(),E.size(),F.size(),G.size());
}

int main(int argc, char **argv)
{
    initialize_blocks();
    // compute all solutions with an initial configuration of the "a" piece
    std::string initial = "aaaa.......................";
    rec_cube = decode(initial);
    initial_solutions.clear();
    find_solutions_a(); // begin recursion to find solutions
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
