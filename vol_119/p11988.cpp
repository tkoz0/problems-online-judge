#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <list>

// since it contains c++ structures (with constructor and destructor)
// node* must be managed with new and delete to ensure string deallocation
struct node
{
    std::string value;
    node *left, *right;
};

node* make_node(const std::string &value)
{
    node *n = new node;
    n->value = value;
    n->left = n->right = nullptr;
    return n;
}

void insert(node **head, node **tail, bool at_end, const std::string& value)
{
    if (value.empty()) return; // skip empty strings
    if (!(*head))
    {
        assert(!(*tail));
        *head = *tail = make_node(value);
    }
    else
    {
        if (at_end)
        {
            (*tail)->right = make_node(value);
            (*tail)->right->left = *tail;
            *tail = (*tail)->right;
        }
        else
        {
            (*head)->left = make_node(value);
            (*head)->left->right = *head;
            *head = (*head)->left;
        }
    }
}

int main(int argc, char **argv)
{
    std::string line;
    while (std::getline(std::cin,line)) // for each test case (1 per line)
    {
        auto itr1 = line.begin();
        node *head = nullptr, *tail = nullptr;
        bool ins_end = true; // insertion point
        for (;;)
        {
            auto itr2 = itr1; // find next []
            while (itr2 != line.end() and *itr2 != '[' and *itr2 != ']') ++itr2;
            insert(&head,&tail,ins_end,std::string(itr1,itr2));
            if (itr2 == line.end()) break; // end of input
            ins_end = (*itr2 == ']');
            itr1 = itr2+1;
        }
        while (head) // print linked list of strings and cleanup memory
        {
            printf("%s",head->value.c_str());
            node *tmp = head;
            head = head->right;
            delete tmp;
        }
        printf("\n");
    }
    return 0;
}
