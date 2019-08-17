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

struct Node * RemoveDuplicates(struct Node * head) {
    if(head == NULL) {
        return head;
    }

    struct Node * p = head;
    struct Node * first = p;

    int val = p->data;
    p = p->next;

    while(p) {
        if(p->data != val) {
            val = p->data;
            first->next = p;
            first = first->next;
        }
        p = p->next;
    }
    first->next = NULL;
    return head;
}

int main(int argc, char *argv[]) {
    struct Node * head = new_node(2);
    head->next = new_node(2);
    head->next->next = new_node(2);
    Print(RemoveDuplicates(head));
    return 0;
}
```
