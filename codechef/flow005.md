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
    int array[6] = {100, 50, 10, 5, 2, 1};
    while( t-- ) {
        int n, answer = 0;
        scanf("%d", &n);

        for(int i = 0; i < 6; i++) {
            answer += (n/array[i]);
            n = n % array[i];
        }

        printf("%d\n", answer);
    }
    return 0;
}
