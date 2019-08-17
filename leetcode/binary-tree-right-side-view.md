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

void _right_side_view(struct node * root, vector<int> &order) {

    if(root == NULL) {
        return;
    }

    queue<struct node *> q;
    q.push(root);
    while(!q.empty()) {
        int s = q.size();
        while(s--) {
            struct node * t = q.front();
            q.pop();

            if(s == 0) {
                order.push_back(t->val);
            }

            if(t->left) {
                q.push(t->left);
            }
            if(t->right) {
                q.push(t->right);
            }
        }
    }
}

vector<int> rightSideView(struct node * root) {
    vector<int> order;
    _right_side_view(root, order);
    return order;
}

int main(int argc, char *argv[]) {
    struct node * root = NULL;

    root = new_node(1);
    root->left = new_node(2);
    root->right = new_node(3);

    vector<int> v = rightSideView(root);
    for(int i = 0 ; i < v.size(); i++) {
        cout << v[i] << endl;
    }

    return 0;
}
```
