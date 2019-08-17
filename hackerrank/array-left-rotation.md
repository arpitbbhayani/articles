```
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

int arr[100010];

void reverse(int start, int end) {
    while(start < end) {
        int t = arr[start];
        arr[start] = arr[end];
        arr[end] = t;
        start++; end--;
    }
}

int main(int argc, char *argv[]) {
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 0 ; i < n ; i ++) {
        scanf("%d", &arr[i]);
    }

    reverse(0, n-1);
    reverse(0, n-k-1);
    reverse(n-k, n-1);

    for(int i = 0 ; i < n ; i ++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
```
