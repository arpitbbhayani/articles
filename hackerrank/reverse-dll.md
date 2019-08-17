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
    struct Node *prev;
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

struct Node * SortedInsert(struct Node * head, int data) {
    struct Node * p = head;
    struct Node * t = new_node(data);

    if(head == NULL) {
        return t;
    }

    while(p->next && p->data <= data) {
        p = p->next;
    }

    if(p == head && data < p->data) {
        t->next= head;
        head->prev = t;
        return t;
    }

    if(p->next == NULL && p->data < data) {
        t->prev = p;
        p->next = t;
    }
    else {
        t->next = p;
        t->prev = p->prev;
        p->prev->next = t;
        p->prev = t;
    }

    return head;
}

struct Node * Reverse(struct Node * head) {
    struct Node * p = head;
    struct Node * prev = NULL;
    while(p) {
        struct Node * t;
        t = p->next;
        p->next = p->prev;
        p->prev = t;

        prev = p;
        p = p->prev;
    }
    return prev;
}

int main(int argc, char *argv[]) {
    struct Node * head = NULL;
    head = SortedInsert(head, 1);
    head = SortedInsert(head, 4);
    head = SortedInsert(head, 2);
    head = SortedInsert(head, 3);
    head = SortedInsert(head, 7);
    head = SortedInsert(head, 6);
    head = SortedInsert(head, 9);
    head = SortedInsert(head, 10);

    Print(head);
    head = Reverse(head);
    Print(head);

    return 0;
}
```
