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

int arr[10010];
int h[20020];
int main(int argc, char *argv[]) {
    int n, d;
    scanf("%d%d", &n, &d);

    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
        h[arr[i]] = 1;
    }

    int count = 0;
    for(int j = 1; j < n - 1; j++) {
        int v = arr[j];
        if(v - d >= 0 && v + d < 20020 && h[v-d] == 1 && h[v + d] == 1) {
            count++;
        }
    }
    printf("%d\n", count);

    return 0;
}
```
