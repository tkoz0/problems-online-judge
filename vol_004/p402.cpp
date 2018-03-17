#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

#include <list>

typedef uint32_t u32;
#define NMAX 50
#define DECK_SIZE 20
#define CARD_MAX 11

// custom safe iterator advancer, prevents incrementing end iterator
template <typename T>
void itr_advance(std::list<T>& l, typename std::list<T>::iterator& itr,
    size_t dist)
{
    while (itr != l.end() and dist--) ++itr;
}

// removes people according to cards in the deck
void process_list(std::list<u32>& people, u32 X, u32 *deck)
{
    for (u32 *d = deck; d != deck + DECK_SIZE and people.size() > X; ++d)
    {
        auto itr = people.begin();
        // move in increments of *d-1 because itr starts at first so it is
        // already counted and erase counts 1 forward by returning itr to next
        while (itr_advance(people, itr, *d - 1),
            people.size() > X and itr != people.end())
            itr = people.erase(itr);
    }
}

int main(int argc, char **argv)
{
    u32 N, X, input_num = 0;
    u32 deck[DECK_SIZE];
    while (++input_num, scanf("%u %u", &N, &X) == 2) // line starts with N X
    {
        assert(1 <= N and N <= NMAX);
        assert(1 <= X and X <= N);
        for (u32 *p = deck; p != deck + DECK_SIZE; ++p) // read 20 card values
        {
            int r = scanf("%u", p);
            assert(r == 1);
            assert(1 <= *p and *p <= CARD_MAX);
        }
        std::list<u32> people;
        for (u32 n = N; n;) // create list of people (numbered 1...N)
            people.push_front(n--);
        assert(people.front() == 1 and people.back() == N);
        process_list(people, X, deck); // remove according to cards in deck
        assert(people.size());
        printf("Selection #%u\n", input_num); // write remaining to stdout
        printf("%u", people.front());
        for (auto itr = people.begin(); ++itr != people.end();)
            printf(" %u", *itr);
        printf("\n\n");
    }
    return 0;
}
