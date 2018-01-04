#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include <iostream>
#include <string>

typedef uint32_t u32;
#define MODULUS 34943

int main(int argc, char **argv)
{
    std::string line;
    while (std::cin)
    {
        std::getline(std::cin, line); // does not include '\n'
        if (line.length() == 1 and line.front() == '#') break; // end input
        u32 value = 0;
        for (auto i = line.begin(); i != line.end(); ++i)
        {
            value <<= 8;
            value += (u32) (*i);
            value %= MODULUS;
        }
        value <<= 16; // shift left 2 bytes (crc addition)
        value %= MODULUS;
        value = MODULUS - value; // value needed to make it divisible by mod
        if (value == MODULUS) value = 0; // 0 instead of modulus itself
        // print both halves of the hex output
        printf("%02X %02X\n", value >> 8, value & 0xFF);
    }
    return 0;
}
