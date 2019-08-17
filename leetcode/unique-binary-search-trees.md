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

int numTrees(int n) {
    int result = 0;
    int * count = (int *) calloc(n+1, sizeof(int));

    count[0] = 1;
    count[1] = 1;

    for(int i = 2; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            count[i] += count[j] * count[i - j - 1];
        }
    }
    result = count[n];
    free(count);

    return result;
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    printf("%d\n", numTrees(n));
    return 0;
}
```
