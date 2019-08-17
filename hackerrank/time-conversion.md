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

int main(int argc, char *argv[]) {
    char t24[32], t12[32];
    scanf("%s", t24);

    int hh24, mm24, ss24, is_am = 0;

    is_am = (t24[8] == 'A');
    t24[2] = t24[5] = t24[8] = '\0';

    hh24 = atoi(&t24[0]);
    mm24 = atoi(&t24[3]);
    ss24 = atoi(&t24[6]);

    if(is_am) {
        if(hh24 == 12) {
            hh24 = 0;
        }
        else {
            // hh24 = hh24;
        }
    }
    else {
        if(hh24 == 12) {
            hh24 = 12;
        }
        else {
            hh24 = hh24 + 12;
        }
    }

    sprintf(t12, "%02d:%02d:%02d", hh24, mm24, ss24);

    printf("%s\n", t12);

    return 0;
}
```
