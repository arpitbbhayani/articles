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

int get_random(struct node * head) {
    int i = 1;
    int random_val = head->val;
    struct node * p = head->next;

    while(p) {
        int j = rand() % (i+1);
        if(j == 0) {
            random_val = p->val;
        }
        i++;
        p = p->next;
    }
    return random_val;
}

int main(int argc, char *argv[]) {
    struct node * head = new_node(10);
    head->next = new_node(1);
    head->next->next = new_node(10);
    head->next->next->next = new_node(20);
    head->next->next->next->next = new_node(100);

    for(int i = 0 ; i < 10; i++) {
        printf("%d\n", get_random(head));
    }

    return 0;
}
```
