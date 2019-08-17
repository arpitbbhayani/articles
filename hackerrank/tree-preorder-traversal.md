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

struct node * new_node(int v) {
    struct node * t = (struct node *) calloc(1, sizeof(struct node));
    t->data = v;
    return t;
}

void preOrder(struct node * root) {
    if(root == NULL) {
        return;
    }

    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

int main(int argc, char *argv[]) {
    struct node * root = new_node(3);
    root->left = new_node(5);
    root->left->left = new_node(1);
    root->left->right = new_node(4);
    root->right = new_node(2);
    root->right->left = new_node(6);

    preOrder(root);
    printf("\n");

    return 0;
}
```
