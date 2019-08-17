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

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {

        int array[110];
        int m, x, y;
        scanf("%d%d%d", &m, &x, &y);

        int p = x * y;

        for(int i = 1 ; i <= 100; i++) {
            array[i] = 0;
        }

        for(int i = 0 ; i < m; i++) {
            scanf("%d", &x);
            array[x] = 1;
            for(int count = 1; count <= p && (x+count) <= 100; count++) {
                array[x + count] = 1;
            }
            for(int count = 1; count <= p && (x-count) >= 1; count++) {
                array[x - count] = 1;
            }
        }

        int answer = 0;
        for(int i = 1; i <= 100; i++) {
            answer += !array[i];
        }
        printf("%d\n", answer);
    }
    return 0;
}
