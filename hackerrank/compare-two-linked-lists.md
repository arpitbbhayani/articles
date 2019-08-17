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

struct Node {
    int data;
    struct Node *next;
};

struct Node * new_node(int v) {
    struct Node * p = (struct Node *) calloc(1, sizeof(struct Node));
    p->data = v;
    return p;
}

int CompareLists(struct Node * headA, struct Node * headB) {
    struct Node * p = headA;
    struct Node * q = headB;

    while(p && q) {
        if(p->data != q->data) {
            return 0;
        }
        p = p->next;
        q = q->next;
    }
    if(p || q) {
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {
    struct Node * head = new_node(1);
    head->next = new_node(2);
    printf("%d\n", CompareLists(head, head));
    return 0;
}
```
