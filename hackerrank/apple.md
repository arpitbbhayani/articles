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
    int s, t, a, b, m, n, x;
    int counta = 0, countb = 0;

    scanf("%d%d", &s, &t);
    scanf("%d%d", &a, &b);
    scanf("%d%d", &m, &n);

    for(int i = 0; i < m; i++) {
        scanf("%d", &x);
        int d = (a + x);
        if(d >= s && d <= t) {
            counta++;
        }
    }

    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
        int d = (b + x);
        if(d >= s && d <= t) {
            countb++;
        }
    }

    printf("%d\n%d\n", counta, countb);
    return 0;
}
