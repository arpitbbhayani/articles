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
    char str[100010];
    readline(str);

    int c = 0, h = 0, e = 0, f = 0;

    for( int i = 0 ; str[i]; i++ ) {
        if(str[i] == 'C') {
            c++;
        }
        else if(str[i] == 'H') {
            if( c > 0 ) {
                c--; h++;
            }
        }
        else if(str[i] == 'E') {
            if( h > 0 ) {
                h--; e++;
            }
        }
        else if(str[i] == 'F') {
            if( e > 0 ) {
                e--; f++;
            }
        }
    }

    printf("%d\n", f);

    return 0;
}
```
