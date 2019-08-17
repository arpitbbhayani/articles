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

char str[1024];
int main(int argc, char *argv[]) {
    stack< char > s;
    scanf("%s", str);
    for(int i = 0 ; str[i]; i++) {
        if(s.empty()) {
            s.push(str[i]);
            continue;
        }

        if(s.top() == str[i]) {
            s.pop();
            continue;
        }

        s.push(str[i]);
    }

    if(s.empty()) {
        printf("Empty String\n");
        return 0;
    }

    stack<char> temp;
    while(!s.empty()) {
        temp.push(s.top());
        s.pop();
    }

    while(!temp.empty()) {
        printf("%c", temp.top());
        temp.pop();
    }
    printf("\n");
    return 0;
}
```
