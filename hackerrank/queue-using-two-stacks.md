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

stack<int> s1;
stack<int> s2;
int front_val;

void enqueue(int x) {
    while(!s2.empty()) {
        s1.push(s2.top());
        s2.pop();
    }
    if(s1.empty()) {
        front_val = x;
    }
    s1.push(x);
}

int dequeue() {
    while(!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
    }
    int x = s2.top();
    s2.pop();
    if(!s2.empty()) {
        front_val = s2.top();
    }
    return x;
}

int front() {
    return front_val;
}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);
    while(t--) {
        int op;
        scanf("%d", &op);
        switch(op) {
            case 1:
                int x;
                scanf("%d", &x);
                enqueue(x);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                printf("%d\n", front());
                break;
        }

    }

    return 0;
}
```
