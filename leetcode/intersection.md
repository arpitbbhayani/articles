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

struct node * getIntersectionNode(struct node * headA, struct node * headB) {
    struct node * a = headA;
    struct node * b = headB;

    int len_a = 0, len_b = 0;

    while(a) { len_a ++; a = a->next; }
    while(b) { len_b ++; b = b->next; }

    if(len_a < len_b) {
        struct node * temp = headA;
        headA = headB;
        headB = temp;

        int t = len_a;
        len_a = len_b;
        len_b = t;
    }

    a = headA; b = headB;
    for(int i = 0 ; i < (len_a - len_b); i++) {
        a = a->next;
    }

    struct node * result = NULL;
    while(a && b) {

        if(a == b) {
            result = a;
            break;
        }

        a = a->next;
        b = b->next;
    }

    return result;
}

int main(int argc, char *argv[]) {
    struct node * head = new_node(2);
    head->next = new_node(1);
    head->next->next = new_node(3);
    head->next->next->next = new_node(4);
    head->next->next->next->next = new_node(5);
    head->next->next->next->next->next = new_node(6);

    printList(head);
    head = getIntersectionNode(head, head);
    printList(head);

    return 0;
}
