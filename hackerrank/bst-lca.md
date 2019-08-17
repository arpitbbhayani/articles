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
    int data;
    struct node * left;
    struct node * right;
};

struct node * new_node(int data) {
    struct node * t = (struct node *) calloc(1, sizeof(struct node));
    t->data = data;
    return t;
}

struct node * lca(struct node * root, int v1, int v2) {

    if(v1 > v2) {
        int t = v1;
        v1 = v2;
        v2 = t;
    }

    struct node * p = root;
    while(p) {
        if(p->data > v1 && p->data < v2) {
            return p;
        }

        if(p->data > v1 && p->data > v2) {
            p = p->left;
        }
        else if(p->data < v1 && p->data < v2) {
            p = p->right;
        }
        else {
            return p;
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    struct node * root = new_node(4);
    root->left = new_node(2);
    root->right = new_node(7);

    root->left->left = new_node(1);
    root->left->right = new_node(3);

    root->right->left = new_node(6);

    printf("%d\n", lca(root, 1, 7)->data);

    return 0;
}
```
