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

int array[110];
int ignored[110];
int tracked[110];

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        for(int i = 1; i <= n; i++ ) {
            array[i] = 0;
            ignored[i] = 0;
            tracked[i] = 0;
        }

        for(int i = 0; i < m; i++ ) {
            int x;
            scanf("%d", &x);
            ignored[x] = 1;
        }

        for(int i = 0; i < k; i++ ) {
            int x;
            scanf("%d", &x);
            tracked[x] = 1;
        }

        int ans1 = 0, ans2 = 0;
        for(int i = 1 ; i <= n; i++ ) {
            if(tracked[i] == 1 && ignored[i] == 1) {
                ans1++;
            }
            if(tracked[i] == 0 && ignored[i] == 0) {
                ans2++;
            }
        }

        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}
