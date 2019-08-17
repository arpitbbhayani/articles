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

char array[7][16] = {"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n;
        scanf("%d", &n);

        int offset = n - 1900;
        for( int i = 1900; i < n; i++ ) {
            if( i % 4 == 0 ) {
                if( i % 100 == 0 && i % 400 != 0 ) {
                    offset += 0;
                }
                else {
                    offset += 1;
                }
            }
            else {
                offset += 0;
            }
        }
        offset = offset % 7;
        printf("%s\n", array[offset]);
    }
    return 0;
}
```
