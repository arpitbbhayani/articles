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

struct node * detectCycle(struct node * head) {
    if(head == NULL || head->next == NULL) {
        return NULL;
    }
    struct node * slow = head;
    struct node * fast = head;

    while(slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast) {
            break;
        }
    }

    if(slow != fast) {
        return NULL;
    }

    slow = head;
    while(slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return fast;
}

int main(int argc, char *argv[]) {
    struct node * head = new_node(1);
    head->next = new_node(2);
    head->next->next = head;

    struct node * temp = detectCycle(head);
    if(temp) {
        printf("Node val = %d\n", temp->val);
    }
    else {
        printf("No Cycle\n");
    }

    return 0;
}
