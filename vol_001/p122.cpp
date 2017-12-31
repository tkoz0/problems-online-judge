#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include <iostream>
#include <string>
#include <utility>
#include <queue>

typedef uint32_t u32;

// solve this problem with signed integers because problem description
// does not explicitly state any requirements about the sign of the numbers
typedef int32_t i32;

// problem requires knowing if nodes have been assigned
// use min signed int value for an unassigned node
#define UNDEF_NODE -2147483648

struct tree_node
{
    i32 n; // leave uninitialized, allow user function to initialize them
    tree_node *l, *r;
};

// reads a character, ignoring whitespace, returns '\0' if reaching EOF
inline char next_ch()
{
    char c;
    while (scanf("%c", &c) == 1)
        if (c != ' ' and c != '\n')
            return c;
    return '\0';
}

void free_tree(tree_node *n)
{
    if (!n) return;
    free_tree(n->l);
    free_tree(n->r);
    free(n);
}

bool all_defined(tree_node *n)
{
    if (!n) return true;
    return (n->n != UNDEF_NODE) and all_defined(n->l) and all_defined(n->r);
}

// returns false if overwriting already defined node
bool insert(tree_node *n, i32 v, std::string &path)
{
    assert(n);
    // find location first
    u32 i = 0;
    while (i != path.length())
    {
        if (path[i] == 'L')
        {
            if (!n->l)
            {
                n->l = (tree_node*) malloc(sizeof(tree_node));
                n->l->n = UNDEF_NODE;
                n->l->l = n->l->r = nullptr;
            }
            n = n->l;
        }
        else
        {
            assert(path[i] == 'R'); // values must be L or R
            if (!n->r)
            {
                n->r = (tree_node*) malloc(sizeof(tree_node));
                n->r->n = UNDEF_NODE;
                n->r->l = n->r->r = nullptr;
            }
            n = n->r;
        }
        ++i;
    }
    // now at insertion point
    // insertion fail if node already defined
    if (n->n != UNDEF_NODE) return false;
    n->n = v;
    return true;
}

// first value determines if a tree could be read
// 2nd value is a non null root node if a valid tree is found
std::pair<bool, tree_node*> make_tree()
{
    char c;
    tree_node *root = (tree_node*) malloc(sizeof(tree_node));
    root->n = UNDEF_NODE;
    root->l = root->r = nullptr; // must be defined null so insert works
    bool valid_tree = true; // set to false if an insert is invalid
    std::string path;
    while ((c = next_ch())) // not reach EOF
    {
        assert(c == '('); // must begin with (
        i32 num;
        if (scanf("%i", &num) == 1)
        {
            c = next_ch();
            assert(c == ','); // separating char
            // next part is the path sequence, use STL string to avoid overflow
            // this works, reads path and ) and the end
            // space separates each node so string wont read more nodes
            std::cin >> path;
            assert(path.back() == ')');
            path.pop_back(); // ignore ), just path of L and R
            // invalid tree, doubly defined node
            if (!insert(root, num, path))
            {
                valid_tree = false;
                break; // outside loop will finish reading this invalid tree
            }
        }
        else // read close ), finished reading this tree
        {
            c = next_ch();
            assert(c == ')');
            break;
        }
    }
    if (!c) // EOF, possibly incomplete tree (not terminated with ())
    {
        free_tree(root); // make sure there are no memory leaks
        return std::make_pair(false, nullptr);
    }
    if (!valid_tree) // finish reading invalid tree
    {
        free_tree(root);
        std::string node_str;
        for (;;)
        {
            // can read entire node as string since specification is that
            // the individual nodes have no whitespace between the ()
            if (std::cin >> node_str)
            {
                if (node_str == std::string("()")) // tree termination
                    return std::make_pair(true, nullptr);
            }
            else return std::make_pair(false, nullptr); // EOF
        }
    }
    // no doubly defined nodes, determine if all trees are defined
    if (!all_defined(root))
    {
        free_tree(root);
        return std::make_pair(true, nullptr);
    }
    return std::make_pair(true, root); // valid tree read
}

void print_level_order(tree_node *root)
{
    assert(root);
    // output root value first (so there are no extra spaces)
    printf("%i", root->n);
    // use std::queue for convenience
    std::queue<tree_node*> q;
    q.push(root->l);
    q.push(root->r);
    while (!q.empty()) // repeatedly pop and print value, push its children
    {
        printf(" %i", q.front()->n);
        if (q.front()->l) q.push(q.front()->l);
        if (q.front()->r) q.push(q.front()->r);
        q.pop();
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    std::pair<bool, tree_node*> result;
    while ((result = make_tree()).first)
    {
        if (!result.second) // invalid binary tree
        {
            printf("not complete\n");
            continue;
        }
        print_level_order(result.second);
        free_tree(result.second);
    }
    return 0;
}
