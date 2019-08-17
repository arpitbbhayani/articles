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

int bits(int n) {
    int count = 0;
    while(n) {
        if(n & 1) count++;
        n = n >> 1;
    }
    return count;
}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int a, b, x;
        scanf("%d%d", &a, &b);

        int answer = 0;
        int bitsa = bits(a);

        while( bitsa != 1 ) {
            answer ++;
            bitsa -= (a & 1);
            a = a >> 1;
        }

        if(a < b) {
            x = a;
            a = b;
            b = x;
        }
        while( a != b ) {
            a = a >> 1;
            answer++;
        }

        //printf("%d %d\n", bitsa, bitsb);

        printf("%d\n", answer);
    }
    return 0;
}
```
