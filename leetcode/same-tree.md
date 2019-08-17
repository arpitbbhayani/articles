```c
/*
 *  Author: Arpit Bhayani
 *  https://arpitbhayani.me
 */
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <deque>
#include <iostream>
#include <list>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#define ll long long

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a > b ? a : b

using namespace std;

int readline(char *str) {
    int i = 0;
    char ch;
    while((ch = getchar()) != '\n') {
        str[i++] = ch;
    }
    str[i] = '\0';
    return i;
}

struct node {
    int val;
    struct node * left;
    struct node *right;
};


struct node * new_node(int val) {
    struct node *t = (struct node *) malloc(sizeof(struct node));
    t->val = val;
    t->left = t->right = NULL;
    return t;
}

int isSameTree(struct node * root_a, struct node * root_b) {

    if(root_a == NULL && root_b == NULL) {
        return 1;
    }

    if(root_a != NULL && root_b != NULL) {
        int l = isSameTree(root_a->left, root_b->left);
        int r = isSameTree(root_a->right, root_b->right);
        return l && r && root_a->val == root_b->val;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    struct node * root = NULL;

    root = new_node(5);
    root->left = new_node(3);
    root->right = new_node(1);
    root->left->left = new_node(7);
    root->left->right = new_node(4);
    root->left->left->right = new_node(2);
    root->right->right = new_node(8);

    cout << isSameTree(root, root) << endl;

    return 0;
}
```
