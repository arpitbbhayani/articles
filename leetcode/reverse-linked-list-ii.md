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

struct node * reverse_list(struct node * head, int m, int n) {

    if(m == n) {
        return head;
    }

    struct node * start = head, * end = NULL;
    struct node * temp = head;
    struct node * prev = NULL, * next = NULL;

    temp = head;
    for(int i = 1 ; i < m; i++) {
        prev = temp;
        temp = temp->next;
    }
    start = temp;

    temp = head;
    for(int i = 1; i < n; i++) {
        temp = temp->next;
        next = temp->next;
    }
    end = temp;

    end->next = NULL;


    struct node * p = start;
    struct node * q = next;
    struct node * r = NULL;

    while(p) {
        r = p->next;
        p->next = q;
        q = p;
        p = r;
    }

    if(prev) {
        prev->next = q;
    }
    else {
        head = q;
    }

    return head;
}

int main(int argc, char *argv[]) {
    struct node * head = new_node(1);
    head->next = new_node(2);
    head->next->next = new_node(3);
    head->next->next->next = new_node(4);
    head->next->next->next->next = new_node(5);
    head->next->next->next->next->next = new_node(6);

    printList(head);
    head = reverse_list(head, 1, 1);
    printList(head);

    return 0;
}
```
