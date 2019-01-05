#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <list>
#include <string>
#include <iostream>

uint32_t team_of[1000000]; // map person number to their team
uint32_t teams[1000][1000]; // store people in teams
uint32_t team_size[1000];

struct person_node
{
    person_node *next;
    uint32_t number;
    person_node(uint32_t n)
    {
        number = n;
        next = nullptr;
    }
};

struct team_node // for makinga linked list of teams
{
    team_node *next;
    uint32_t team_num;
    person_node *head, *tail; // linked list of people in line
    team_node(uint32_t tn)
    {
        team_num = tn;
        next = nullptr;
        head = tail = nullptr;
    }
    void push(uint32_t pn)
    {
        if (tail)
        {
            tail->next = new person_node(pn);
            tail = tail->next;
        }
        else head = tail = new person_node(pn);
    }
    uint32_t pop()
    {
        assert(head);
        uint32_t ret_val = head->number;
        person_node *tmp = head;
        head = head->next;
        delete tmp;
        if (!head) tail = nullptr;
        return ret_val;
    }
    bool empty() { return !head; }
};

team_node *team_pos[1000]; // map teams to their linked list node in the line

struct LINE
{
    team_node *head, *tail;
    LINE()
    {
        head = tail = nullptr;
    }
    void push_person(uint32_t pn)
    {
        if (!team_pos[team_of[pn]]) // first in line for their team
        {
            if (!head) // first team in list
            {
                head = tail = new team_node(team_of[pn]);
                head->push(pn);
                team_pos[team_of[pn]] = head;
            }
            else
            {
                tail->next = new team_node(team_of[pn]);
                tail = tail->next;
                tail->push(pn);
                team_pos[team_of[pn]] = tail;
            }
        }
        else team_pos[team_of[pn]]->push(pn);
    }
    uint32_t pop_person()
    {
        assert(head);
        uint32_t ret_val = head->pop();
        if (head->empty()) // must remove from this list
        {
            team_node *tmp = head;
            head = head->next;
            if (!head) tail = nullptr;
            team_pos[tmp->team_num] = nullptr;
            delete tmp;
        }
        return ret_val;
    }
};

int main(int argc, char **argv)
{
    uint32_t t, t_num, p_num, to_queue;
    int scanfr;
    std::string command;
    uint32_t scenario_num = 0;
    while (++scenario_num, scanf("%u",&t) == 1) // read number of teams
    {
        if (!t) break; // 0 terminates
        for (t_num = 0; t_num != t; ++t_num) // input each team
        {
            scanfr = scanf("%u",&(team_size[t_num])); // team size
            assert(scanfr == 1);
            for (p_num = 0; p_num != team_size[t_num]; ++p_num)
            {
                scanfr = scanf("%u",&(teams[t_num][p_num]));
                assert(scanfr == 1);
                team_of[teams[t_num][p_num]] = t_num;
            }
        }
        LINE line = LINE();
        for (t_num = 0; t_num != t; ++t_num) team_pos[t_num] = nullptr;
        printf("Scenario #%u\n",scenario_num);
        while (std::cin >> command)
        {
            if (command[0] == 'S') break; // stop
            if (command[0] == 'E') // enqueue
            {
                scanfr = scanf("%u",&to_queue);
                assert(scanfr == 1);
                line.push_person(to_queue);
            }
            else // dequeue (first)
                printf("%u\n",line.pop_person());
        }
        printf("\n");
    }
    return 0;
}
