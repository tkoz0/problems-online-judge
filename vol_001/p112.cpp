#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include <utility>

// solve this problem with signed integers because problem description
// does not explicitly state any requirements about the sign of the numbers
typedef int32_t i32;

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

tree_node* make_tree()
{
    char c;
    c = next_ch();
    assert(c == '('); // must begin with (
    i32 num;
    tree_node *result;
    if (scanf("%i", &num) == 1) // tree has number
    {
        result = (tree_node*) malloc(sizeof(tree_node));
        result->n = num;
        result->l = make_tree(); // recursively create subtrees
        result->r = make_tree();
    }
    else result = NULL; // empty tree
    c = next_ch();
    assert(c == ')'); // must end with )
    return result;
}

void free_tree(tree_node *root) // clear dynamic memory
{
    if (!root) return;
    free_tree(root->l);
    free_tree(root->r);
    free(root);
}

bool sums_to(i32 v, tree_node *t, i32 s)
{
    assert(t);
    s += t->n; // sequence sum up to this point
    if (t->l) // not leaf, left tree
    {
        // if 2 subtrees, return whether a path exists down either direction
        if (t->r) return sums_to(v, t->l, s) or sums_to(v, t->r, s);
        return sums_to(v, t->l, s); // only left subtree
    }
    if (t->r) return sums_to(v, t->r, s); // only right subtree
    return s == v; // is leaf node
}

void _debug_print_tree(tree_node *t, uint32_t l)
{
    if (!t) return;
    _debug_print_tree(t->r, l + 1);
    uint32_t ll = l;
    while (ll--) printf("  ");
    printf("%i\n", t->n);
    _debug_print_tree(t->l, l + 1);
}

// similar but without creating an explicit binary tree
// first bool is true if subtree not empty, second is true if path sum found
std::pair<bool, bool> search_tree(i32 sum, i32 val)
{
    char c;
    c = next_ch();
    assert(c == '('); // begin node
    i32 num;
    if (scanf("%i", &num) == 1) // not empty node
    {
        std::pair<bool, bool> l, r;
        sum += num;
        l = search_tree(sum, val);
        r = search_tree(sum, val);
        c = next_ch();
        assert(c == ')'); // end node
        // if either subtree is not empty, this node is not a leaf
        if (l.first or r.first)
            // if successful path found deeper in the tree
            return std::make_pair(true, l.second or r.second);
        // this node is part of a subtree so it exists, it is also a leaf
        return std::make_pair(true, sum == val);
    }
    else // empty
    {
        c = next_ch();
        assert(c == ')'); // end tree
        return std::make_pair(false, false);
    }
}

int main(int argc, char **argv)
{
    i32 sum_to;
//    tree_node *root;
    while (scanf("%i", &sum_to) == 1)
    {
        std::pair<bool, bool> result = search_tree(0, sum_to);
        if (result.first and result.second)
            printf("yes\n");
        else printf("no\n");
//        root = make_tree();
//        _debug_print_tree(root, 0);
//        if (root and sums_to(sum_to, root, 0))
//            printf("yes\n");
//        else printf("no\n");
//        free_tree(root);
    }
    return 0;
}
