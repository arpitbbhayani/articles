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

int main(int argc, char *argv[]) {

    int n, k, sum;
    int *arr;

    scanf("%d%d", &n, &k);
    arr = (int *) malloc(sizeof(int) * n);
    for(int i = 0 ; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &sum);

    int total_sum = 0;
    for(int i = 0 ; i < n; i++) {
        total_sum += arr[i];
    }

    total_sum -= arr[k];
    total_sum = total_sum / 2;

    if(sum - total_sum == 0) {
        printf("Bon Appetit\n");
    }
    else {
        printf("%d\n", sum - total_sum);
    }

    free(arr);
    return 0;
}
```
