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
#define MAX(a, b) a > b ? a : b

using namespace std;

int readline(char *str) {
    int i = 0;
    char ch;
    while((ch = getchar()) != '\n') {
        str[i++] = ch;
    }
    str[i] = '\0';
    return i;
}

int main(int argc, char *argv[]) {

    int x1, v1, x2, v2;
    scanf("%d%d%d%d", &x1, &v1, &x2, &v2);

    if(x1 > x2) {
        // Ensuring x1 is always behind x1
        int t = x1;
        x1 = x2;
        x2 = t;

        t = v1;
        v1 = v2;
        v2 = t;
    }

    if(x1 == x2 && v1 == v2) {
        printf("YES\n");
    }
    else if(x1 == x2 && v1 > v2) {
        printf("NO\n");
    }
    else if(x1 <= x2 && v1 <= v2) {
        printf("NO\n");
    }
    else {
        if( (x2 - x1) % (v1 - v2) == 0 ) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }

    return 0;
}
