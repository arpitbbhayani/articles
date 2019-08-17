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

vector<int> in_order(struct node * root) {
    vector<int> order;
    stack<struct node *> s;
    struct node * p = root;

    int is_done = 0;

    while(is_done == 0) {
        if(p != NULL) {
            s.push(p);
            p = p->left;
        }
        else {
            if(!s.empty()) {
                struct node * t = s.top();
                s.pop();
                order.push_back(t->val);
                p = t->right;
            }
            else {
                is_done = 1;
            }
        }
    }
    return order;
}

int main(int argc, char *argv[]) {
    struct node * root = NULL;

    root = new_node(1);
    root->left = new_node(2);
    root->right = new_node(3);
    root->left->left = new_node(4);
    root->left->right = new_node(5);
    root->right->left = new_node(6);

    vector<int> order = in_order(root);
    for(vector<int>::iterator itr = order.begin(); itr != order.end(); itr++) {
        printf("%d ", *itr);
    }
    printf("\n");

    return 0;
}
```
