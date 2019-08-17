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

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);

    int *arr = (int *) calloc(n, sizeof(int));
    int *jumps = (int *) calloc(n, sizeof(int));

    for(int i = 0 ; i < n; i++) {
        scanf("%d", &arr[i]);
        jumps[i] = 0;
    }

    jumps[0] = 0;
    jumps[1] = (arr[1] == 1) ? 0 : jumps[0] + 1;
    for(int i = 2 ; i < n ; i++) {
        int first = i - 1;
        int second = i - 2;
        if(arr[second] == 1) {
            jumps[i] = jumps[first] + 1;
        }
        else {
            jumps[i] = jumps[second] + 1;
        }
    }

    printf("%d\n", jumps[n-1]);

    free(arr);
    return 0;
}
```
