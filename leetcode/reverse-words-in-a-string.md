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

void reverse(char *str, int start, int end) {
    while(start < end) {
        char t = str[start];
        str[start] = str[end];
        str[end] = t;

        start++;
        end--;
    }
}

void reverseWords(char *s) {
    char *str = s;
    int length = 0;

    while(str[length]) { length++; }

    // remove trailing spaces
    int i = length - 1;
    while(str[i] == ' ') {
        i--;
    }
    str[i + 1] = '\0';

    // remove leading spaces
    i = 0;
    while(str[i] == ' ') {
        i++;
    }
    str = &str[i];

    // remove multiple spaces in between
    int index = 0;
    i = 0;
    while(str[i]) {
        if(str[i] == ' ') {
            while(str[i] == ' ') {
                i++;
            }
            i--;
        }
        str[index++] = str[i++];
    }
    str[index] = '\0';

    length = index;

    reverse(str, 0, length - 1);

    int start = 0, end = 0;
    for(int i = 0 ; str[i]; i++) {
        if(str[i] == ' ') {
            end = i - 1;
            reverse(str, start, end);
            start = i + 1;
        }
    }
    reverse(str, start, length - 1);

    index = 0;
    i = 0;
    while(str[i]) {
        s[index++] = str[i++];
    }
    s[index] = '\0';
}

int main(int argc, char *argv[]) {
    char str[1024];
    readline(str);
    reverseWords(str);
    printf("%s", str);
    return 0;
}
```
