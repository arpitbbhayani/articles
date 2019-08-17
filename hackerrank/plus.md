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
    int t, x;
    scanf("%d", &t);

    int c0 = 0, cp = 0, cn = 0;

    for(int i = 0; i < t; i++) {
        cin >> x;
        if(x > 0) {
            cp++;
        }
        else if(x < 0) {
            cn++;
        }
        else {
            c0++;
        }
    }

    printf("%f\n%f\n%f\n", cp/(float)t, cn/(float)t, c0/(float)t);

    return 0;
}
