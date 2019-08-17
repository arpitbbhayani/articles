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

int is_pow_2(unsigned ll int n) {
    return n && ((n & (n-1)) == 0);
}

int leftmost_set_bit(unsigned ll int n) {
    int x = 0;
    for(int i = 0 ; n ; i++) {
        if(n & 1) {
            x = i + 1;
        }
        n >>= 1;
    }
    return x;
}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while(t--) {
        int count = 0;
        unsigned ll int n;
        cin >> n;

        n--;
        while(n) {
            n &= (n-1);
            count++;
        }

        if(count & 1) {
            printf("Louise\n");
        }
        else {
            printf("Richard\n");
        }

    }

    return 0;
}
