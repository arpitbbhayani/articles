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

void deleteNode(struct node * node) {
    struct node * p = node;
    struct node * next = p->next;

    if(next != NULL) {
        int t = p->val;
        p->val = next->val;
        next->val = t;

        p->next = p->next->next;
        free(next);
    }
}

int main(int argc, char *argv[]) {
    struct node * head = new_node(1);
    head->next = new_node(2);
    head->next->next = new_node(3);
    head->next->next->next = new_node(4);
    head->next->next->next->next = new_node(5);
    head->next->next->next->next->next = new_node(6);

    deleteNode(head->next->next->next->next->next);
    printList(head);

    return 0;
}
