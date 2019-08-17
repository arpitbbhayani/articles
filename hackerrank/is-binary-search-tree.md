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

bool _check(struct node * root, int * m) {
    if(root == NULL) {
        return true;
    }

    bool l = _check(root->left, m);
    if(root->data <= *m) {
        return false;
    }
    *m = root->data;
    bool r = _check(root->right, m);
    return l && r;
}

bool checkBST(struct node * root) {
    int m = -1;
	return _check(root, &m);
}

int main(int argc, char *argv[]) {
    struct node * root = new_node(3);
    root->left = new_node(1);
    root->right = new_node(4);

    printf("%d\n", checkBST(root));

    return 0;
}
```
