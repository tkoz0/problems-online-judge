#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>

typedef uint32_t u32;

#define MAX_K 20
#define MAX_E 20
#define MAX_KW_LEN 20
#define MAX_EX_LEN 70
#define SEP "\".,!?"

void _debug_kw_sanity_check(std::vector<std::string>& kws)
{
    for (auto kw : kws)
        for (auto c : kw)
            assert('a' <= c and c <= 'z');
}

// reads words from an excuse into separate strings, store in a vector
std::vector<std::string> parse_words(std::string& str)
{
    static std::string seps = std::string(SEP);
    std::vector<std::string> words;
    for (auto itr = str.begin(); itr != str.end(); ++itr)
    {
        if ('A' <= *itr and *itr <= 'Z') // convert to lower
        {
            *itr = 'a' + (*itr - 'A');
            continue;
        }
        if ('0' <= *itr and *itr <= '9') // ignore numbers
        {
            *itr = ' ';
            continue;
        }
        for (auto c : seps) // ignore separators
            if (*itr == c)
            {
                *itr = ' ';
                break;
            }
    }
    std::stringstream ss(str); // extract words with string stream
    std::string str2;
    while (ss >> str2)
        words.push_back(str2);
    return words;
}

void print_matches(const std::vector<std::string>& kws,
    std::vector<std::tuple<std::string, u32, std::vector<std::string> > >& exs,
    u32 set)
{
    printf("Excuse Set #%u\n", set);
    for (auto ex = exs.begin(); ex != exs.end(); ++ex) // count keywords in each
        for (auto ew : std::get<2>(*ex))
            for (auto kw : kws)
                if (kw == ew)
                {
                    ++std::get<1>(*ex);
                    break;
                }
    // sort by number of keywords
    std::stable_sort(exs.begin(), exs.end(),
        [](const std::tuple<std::string, u32, std::vector<std::string> >& a,
           const std::tuple<std::string, u32, std::vector<std::string> >& b)
        {
            return std::get<1>(a) > std::get<1>(b);
        }
    );
    u32 worst = std::get<1>(exs.front()); // worst number of keywords
    for (auto ex : exs) // print excuses
    {
        if (std::get<1>(ex) != worst) break; // not worst
        std::cout << std::get<0>(ex) << std::endl;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    u32 K, E, set = 0;
    std::string str;
    std::vector<std::string> kw;
    std::vector<std::tuple<std::string, u32, std::vector<std::string> > > ex;
    while (++set, scanf("%u %u", &K, &E) == 2)
    {
        assert(K and K <= MAX_K);
        assert(E and E <= MAX_E);
        kw.clear();
        while (K--) // read keywords
        {
            if (!(std::cin >> str)) assert(0);
            assert(str.length() <= MAX_KW_LEN);
            kw.push_back(str);
        }
        std::getline(std::cin, str); // distard rest of line after last keyword
        _debug_kw_sanity_check(kw);
        ex.clear();
        while (E--) // parse words in excuses
        {
            std::getline(std::cin, str);
            assert(str.length());
            std::tuple<std::string, u32, std::vector<std::string> > tp;
            std::get<0>(tp) = str;
            std::get<1>(tp) = 0;
            std::get<2>(tp) = parse_words(str);
            ex.push_back(tp);
        }
        print_matches(kw, ex, set);
    }
    return 0;
}
