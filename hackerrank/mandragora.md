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

ll int arr[100010];

int compar(const void * a, const void * b) {
    return (*(int *)a) > (*(int *)b);
}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while(t--) {
        int n;
        ll int sum = 0;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%lld", &arr[i]);
            sum += arr[i];
        }

        qsort(arr, n , sizeof(ll int), compar);

        ll int op, tp, temp_sum = sum;
        op = (0 + 1) * temp_sum;
        for(int x = 1; x < n; x++) {
            temp_sum -= arr[x-1];
            tp = (x + 1) * temp_sum;
            if(tp < op) {
                break;
            }
            op = MAX(tp, op);
        }
        printf("%lld\n", op);
    }

    return 0;
}
```
