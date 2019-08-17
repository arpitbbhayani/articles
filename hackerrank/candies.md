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

ll int arr[100010];
int h1[100010];
int h2[100010];

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        scanf("%lld", &arr[i]);
    }

    ll int prev = arr[0];
    h1[0] = 1;
    h2[n-1] = 1;

    for(int i = 1 ; i < n; i++) {
        if(arr[i] > prev) {
            h1[i] = h1[i-1] + 1;
        }
        else {
            h1[i] = 1;
        }
        prev = arr[i];
    }

    prev = arr[n-1];
    for(int i = n-1; i >= 0; i--) {
        if(arr[i] > arr[i+1]) {
            h2[i] = h2[i+1] + 1;
        }
        else {
            h2[i] = 1;
        }
        prev = arr[i];
    }

    ll int count = 0;
    for(int i = 0 ; i < n ; i++) {
        int m = MAX(h1[i], h2[i]);
        count += m;
    }
    printf("%lld\n", count);
    return 0;
}
