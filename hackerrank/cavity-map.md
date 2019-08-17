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

char arr[110][110];

int main(int argc, char *argv[]) {
    int n;
    cin >> n;

    for(int i = 0 ; i  < n ; i++) {
        scanf("%s", arr[i]);
    }

    for(int i = 1; i < n-1; i++) {
        for(int j = 1; j < n -1 ; j++) {
            int d = arr[i][j] - '0';
            if(arr[i][j] != 'X' && ((arr[i-1][j] - '0') < d &&
                (arr[i+1][j] - '0') < d && (arr[i][j - 1] - '0') < d &&
                (arr[i][j+1] - '0') < d)) {
                arr[i][j] = 'X';
            }
        }
    }

    for(int i = 0 ; i < n ; i++) {
        printf("%s\n", arr[i]);
    }

    return 0;
}
```
