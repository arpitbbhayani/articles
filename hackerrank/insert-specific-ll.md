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

struct Node * InsertNth(Node *head, int data, int position) {
    struct Node * p = head;
    struct Node * t = new_node(data);

    if(p == NULL && position == 0) {
        return t;
    }

    if(position == 0) {
        t->next = head;
        return t;
    }

    while(--position) {
        p = p->next;
    }
    t->next = p->next;
    p->next = t;

    return head;
}

int main(int argc, char *argv[]) {
    struct Node * head = new_node(3);
    head = InsertNth(head, 4, 0);
    head = InsertNth(head, 5, 2);
    Print(head);
    return 0;
}
```
