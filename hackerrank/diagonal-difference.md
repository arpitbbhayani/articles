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

int mat[200][200];

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);

    for(int i = 0;i < n; i++) {
        for(int j = 0; j <n; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    ll int sum1 = 0, sum2 = 0;
    for(int i = 0 ; i < n; i++) {
        sum1 += mat[i][i];
        sum2 += mat[i][n-1-i];
    }
    cout << abs(sum1-sum2) << endl;

    return 0;
}
```
