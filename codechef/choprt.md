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
        ll int a = 0, b = 0;
        char str[64];

        scanf("%s", str);
        for(int i = 0 ; str[i]; i++) {
            a = a * 10 + (str[i] - '0');
        }

        scanf("%s", str);
        for(int i = 0 ; str[i]; i++) {
            b = b * 10 + (str[i] - '0');
        }

        if(a < b) {
            printf("<\n");
        }
        if(a == b) {
            printf("=\n");
        }
        if(a > b) {
            printf(">\n");
        }

    }
    return 0;
}
