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

int max(int a, int b) {
    return a > b ? a : b;
}

int _max_sum(struct node * root, int * sum) {
    if(root == NULL) {
        return 0;
    }

    int l = _max_sum(root->left, sum);
    int r = _max_sum(root->right, sum);

    int lr = l + root->val;
    int rr = r + root->val;
    int s = root->val;
    int lrs = l + r + s;

    *sum = max(*sum, max(lr, max(rr, max(s, lrs))));
    return max(lr, max(rr, s)); // Not considering l + r + s
}

int maxPathSum(struct node * root) {
    int sum = INT_MIN;
    _max_sum(root, &sum);
    return sum;
}

int main(int argc, char *argv[]) {
    struct node * root = NULL;

    root = new_node(1);
    root->left = new_node(2);
    root->right = new_node(3);

    printf("%d\n", maxPathSum(root));

    return 0;
}
```
