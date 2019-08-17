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

ll int fact[22];

void calculate() {
    fact[0] = 1;
    for(int i = 1; i <= 21; i++ ) {
        fact[i] = i * fact[i-1];
    }
}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    calculate();

    while( t-- ) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", fact[n]);
    }
    return 0;
}
