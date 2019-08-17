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

ll int array[52];

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n;
        scanf("%d", &n);
        for( int i = 0 ; i < n ; i ++ ) {
            scanf("%lld", &array[i]);
        }

        int answer = 0;
        int sum = 0, pro = 1;

        for(int start = 0 ; start < n ; start++ ) {
            sum = array[start];
            pro = array[start];
            for(int end = start + 1 ; end < n ; end++ ) {
                sum += array[end];
                pro *= array[end];
                if( sum == pro ) {
                    //printf("start = %d, end = %d, sum & pro = %d\n", start, end, pro);
                    answer++;
                }
            }
        }

        printf("%d\n", answer + n);
    }
    return 0;
}
```
