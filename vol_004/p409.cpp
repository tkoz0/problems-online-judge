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
typedef std::vector<std::string> vecstr;
typedef std::tuple<std::string, u32, vecstr> excuse;

#define MAX_K 20
#define MAX_E 20
#define MAX_KW_LEN 20
#define MAX_EX_LEN 70
#define SEP "\".,!?"

void _debug_kw_sanity_check(vecstr& kws)
{
    for (auto kw : kws)
        for (auto c : kw)
            assert('a' <= c and c <= 'z');
}

void _debug_ex_sanity_check(std::vector<excuse>& exs)
{
    for (auto ex : exs)
        for (auto w : std::get<2>(ex))
            for (auto c : w)
                assert('a' <= c and c <= 'z');
}

// reads words from an excuse into separate strings, store in a vector
vecstr parse_words(std::string& str)
{
    static std::string seps = std::string(SEP);
    vecstr words;
    for (auto itr = str.begin(); itr != str.end(); ++itr)
    {
        if ('A' <= *itr and *itr <= 'Z') // convert to lower
            *itr = 'a' + (*itr - 'A');
        else if ('a' <= *itr and *itr <= 'z') // ignore lower
            continue;
        else *itr = ' ';
    }
    std::stringstream ss(str); // extract words with string stream
    std::string str2;
    while (ss >> str2)
        words.push_back(str2);
    return words;
}

void print_matches(const vecstr& kws, std::vector<excuse>& exs, u32 set)
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
    u32 worst = 0;
    for (auto ex : exs) worst = std::max(worst, std::get<1>(ex));
/*    // sort by number of keywords
    std::stable_sort(exs.begin(), exs.end(),
        [](const std::tuple<std::string, u32, std::vector<std::string> >& a,
           const std::tuple<std::string, u32, std::vector<std::string> >& b)
        {
            return std::get<1>(a) > std::get<1>(b);
        }
    );*/
    for (auto ex : exs) // print excuses
        if (std::get<1>(ex) == worst)
            std::cout << std::get<0>(ex) << std::endl;
    printf("\n");
}

int main(int argc, char **argv)
{
    u32 K, E, set = 0;
    std::string str;
    vecstr kw;
    std::vector<excuse> ex;
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
            excuse tp;
            std::get<0>(tp) = str;
            std::get<1>(tp) = 0;
            std::get<2>(tp) = parse_words(str);
            ex.push_back(tp);
        }
        _debug_ex_sanity_check(ex);
        print_matches(kw, ex, set);
    }
    return 0;
}
