```
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

struct node * lowestCommonAncestor(struct node * root, struct node * p, struct node * q) {
    if(root == NULL) {
        return NULL;
    }

    if(root->val < p->val && root->val < q->val) {
        return lowestCommonAncestor(root->right, p, q);
    }

    if(root->val > p->val && root->val > q->val) {
        return lowestCommonAncestor(root->left, p, q);
    }

    return root;
}

int main(int argc, char *argv[]) {
    struct node * root = NULL;

    root = new_node(2);
    root->left = new_node(1);
    root->right = new_node(3);

    lowestCommonAncestor(root, root->left, root->left);

    return 0;
}
```
