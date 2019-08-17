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

struct Node * Reverse(struct Node * head) {

    if(head == NULL) {
        return head;
    }

    struct Node * p = NULL;
    struct Node * q = head;
    struct Node * r = q->next;

    while(q) {
        r = q->next;
        q->next = p;
        p = q;
        q = r;
    }

    return p;
}

int main(int argc, char *argv[]) {
    struct Node * head = new_node(1);
    Print(head);
    head = Reverse(head);
    Print(head);
    return 0;
}
```
