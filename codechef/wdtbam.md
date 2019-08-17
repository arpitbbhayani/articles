/*
 *  Author: Arpit Bhayani
 *  https://arpitbhayani.me
 */
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cstring>
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

ll int array[1010];
char str1[1010], str2[1010];

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n;
        scanf("%d", &n);
        scanf("%s%s", str1, str2);
        for(int i =0 ; i <= n ; i++ ) {
            scanf("%lld", &array[i]);
        }

        int count = 0;
        for( int i = 0 ; i < n ; i++ ) {
            count += (str1[i] == str2[i]);
        }

        if(count == n) {
            printf("%lld\n", array[count]);
        }
        else {
            ll int m = -1;
            for( int i = 0; i <= count; i++ ) {
                m = (array[i] > m) ? array[i] : m;
            }
            printf("%lld\n", m);
        }


    }
    return 0;
}
