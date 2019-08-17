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
    int data;
    struct node * left;
    struct node * right;
};

struct node * new_node(int v) {
    struct node * t = (struct node *) calloc(1, sizeof(struct node));
    t->data = v;
    return t;
}

struct node * insert(struct node * root, int value) {
    if(root == NULL) {
        return new_node(value);
    }

    struct node * p = root;
    while(p->left != NULL || p->right != NULL) {
        if(value <= p->data) {
            p = p->left;
        }
        else {
            p = p->right;
        }
    }

    if(value <= p->data) {
        p->left = new_node(value);
    }
    else {
        p->right = new_node(value);
    }
    return root;
}

int main(int argc, char *argv[]) {
    struct node * root = new_node(4);
    root->left = new_node(2);
    root->right = new_node(7);

    root->left->left = new_node(1);
    root->left->right = new_node(3);

    insert(root, 6);

    return 0;
}
```
