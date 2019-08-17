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

struct Node * new_node(int v) {
    struct Node * p = (struct Node *) calloc(1, sizeof(struct Node));
    p->data = v;
    return p;
}

int FindMergeNode(Node * headA, Node * headB) {
    int lp = 0, lq = 0;
    struct Node * p = headA;
    struct Node * q = headB;

    while(p) {
        lp++;
        p = p->next;
    }

    while(q) {
        lq++;
        q = q->next;
    }

    p = headA; q = headB;
    if(lp > lq) {
        struct Node * t = p;
        p = q;
        q = t;

        int tt = lp;
        lp = lq;
        lq = tt;
    }

    for(int i = 0 ; i < (lq-lp); i++) {
        q = q->next;
    }

    while(p && q) {
        if(p == q) {
            return p->data;
        }
        p = p->next;
        q = q->next;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    struct Node * head = new_node(1);
    head->next = new_node(2);
    head->next->next = new_node(3);
    cout << FindMergeNode(head) << endl;
    return 0;
}
```
