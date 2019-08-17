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

struct Node * new_node(int v) {
    struct Node * p = (struct Node *) calloc(1, sizeof(struct Node));
    p->data = v;
    return p;
}

void ReversePrint(struct Node * head) {
    stack<int> s;
    while(head) {
        s.push(head->data);
        head = head->next;
    }

    while(!s.empty()) {
        printf("%d\n", s.top());
        s.pop();
    }
}

int main(int argc, char *argv[]) {
    struct Node * head = new_node(3);
    head->next = new_node(4);
    ReversePrint(head);
    return 0;
}
```
