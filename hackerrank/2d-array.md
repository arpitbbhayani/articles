```c
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

int arr[6][6];
int main(int argc, char *argv[]) {
    int ans = INT_MIN;

    for(int i = 0; i < 6; i++) {
        for(int j = 0 ; j < 6; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    for(int i = 1; i < 5; i++) {
        for(int j = 1; j < 5; j++) {
            int temp = arr[i][j] + arr[i-1][j] + arr[i-1][j-1] + arr[i-1][j+1] + arr[i+1][j] + arr[i+1][j-1] + arr[i+1][j+1];
            ans = MAX(ans, temp);
        }
    }

    printf("%d\n", ans);

    return 0;
}
```
