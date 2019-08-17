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
    struct node * next;
};

struct node * new_node(int d) {
    struct node * t = (struct node *) calloc(1, sizeof(struct node));
    t->val = d;
    return t;
}

void printList(struct node * head) {
    struct node * p = head;
    while(p) {
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
}

struct node * oddEvenList(struct node * head) {
    if(head == NULL) {
        return NULL;
    }
    struct node * odd_head = NULL, * even_head = NULL;
    struct node * odd_tail = NULL, * even_tail = NULL;
    struct node * odd_tail_prev = NULL;

    odd_head = odd_tail = head;
    even_head = even_tail = head->next;

    while(odd_tail && even_tail) {
        if(odd_tail->next) {
            odd_tail->next = odd_tail->next->next;
        }

        if(even_tail->next) {
            even_tail->next = even_tail->next->next;
        }

        odd_tail_prev = odd_tail;
        odd_tail = odd_tail->next;
        even_tail = even_tail->next;
    }

    if(odd_tail) {
        odd_tail->next = even_head;
    }
    else {
        odd_tail_prev->next = even_head;
    }
    return odd_head;
}

int main(int argc, char *argv[]) {
    struct node * head = new_node(1);
    head->next = new_node(2);
    head->next->next = new_node(3);
    head->next->next->next = new_node(4);
    head->next->next->next->next = new_node(5);
    head->next->next->next->next->next = new_node(6);

    head = oddEvenList(head);
    printList(head);

    return 0;
}
```
