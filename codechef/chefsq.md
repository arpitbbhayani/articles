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

ll int array1[100000];
ll int array2[100000];

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {

        int n;
        scanf("%d", &n);
        for(int i = 0 ; i < n ; i++) {
            ll int x;
            scanf("%lld", &x);
            array1[i] = x;
        }

        int m;
        scanf("%d", &m);
        for(int i = 0 ; i < m ; i++) {
            ll int x;
            scanf("%lld", &x);
            array2[i] = x;
        }

        int k = 0, match = 0;
        for( int j = 0 ; j < m ; j++ ) {
            for( int i = k ; i < n; i++ ) {
                if( array1[i] == array2[j] ) {
                    k = i + 1;
                    match ++;
                    break;
                }
            }
        }

        if(match == m) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
    return 0;
}
