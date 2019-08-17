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

struct node * reverse_list(struct node * head) {
    struct node * p = head;
    struct node * q = NULL;
    struct node * r = NULL;

    while(p) {
        r = p->next;
        p->next = q;
        q = p;
        p = r;
    }

    return q;
}

bool isPalindrome(struct node * head) {

    if(head == NULL || head->next == NULL) {
        return 1;
    }

    int is_palin = 1;
    struct node * p = head;
    struct node * mid = head;
    struct node * prev = head;

    while(p && p->next) {
        prev = mid;
        mid = mid->next;
        p = p->next->next;
    }

    prev->next = NULL;
    mid = reverse_list(mid);

    struct node * a = head;
    struct node * b = mid;

    while(a) {
        if(a->val != b->val) {
            is_palin = 0;
            break;
        }
        a = a->next;
        b = b->next;
    }

    mid = reverse_list(mid);
    prev->next = mid;

    return is_palin;
}

int main(int argc, char *argv[]) {
    struct node * head = new_node(2);
    head->next = new_node(1);
    head->next->next = new_node(2);
    head->next->next->next = new_node(4);
    head->next->next->next->next = new_node(5);
    head->next->next->next->next->next = new_node(6);

    printList(head);
    printf("%d\n", isPalindrome(head));
    printList(head);

    return 0;
}
```
