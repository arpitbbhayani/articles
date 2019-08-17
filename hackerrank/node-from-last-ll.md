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

struct Node {
    int data;
    struct Node *next;
};

void Print(struct Node *head) {
    struct Node *p = head;
    while(p) {
        printf("%d\n", p->data);
        p = p->next;
    }
}

struct Node * new_node(int v) {
    struct Node * p = (struct Node *) calloc(1, sizeof(struct Node));
    p->data = v;
    return p;
}

int GetNode(struct Node * head,int positionFromTail) {
    struct Node * p = head;
    struct Node * q = p;

    while(positionFromTail--) {
        q = q->next;
    }

    while(q->next) {
        p = p->next;
        q = q->next;
    }

    return p->data;
}

int main(int argc, char *argv[]) {
    struct Node * headA = new_node(1);
    headA->next = new_node(2);
    headA->next->next = new_node(4);

    printf("%d\n", GetNode(headA, 0));
    printf("%d\n", GetNode(headA, 1));
    printf("%d\n", GetNode(headA, 2));
    return 0;
}
```
