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

int arr[100010];
int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while(t--) {
        int n;
        cin >> n;

        for(int i = 0 ; i < n ; i++) {
            scanf("%d", &arr[i]);
        }

        int curr_max = arr[0], msub = arr[0];
        for(int i = 1 ; i < n ; i++) {
            curr_max = MAX(curr_max + arr[i], arr[i]);
            msub = MAX(msub, curr_max);
        }

        int sum = 0, allnegs = 1, max_neg_val = INT_MIN;
        for(int i = 0 ; i < n; i++) {
            if(arr[i] >= 0) {
                allnegs = 0;
                sum += arr[i];
            }
            else {
                max_neg_val = MAX(max_neg_val, arr[i]);
            }
        }

        if(allnegs == 1) {
            sum = max_neg_val;
        }

        printf("%d %d\n", msub, sum);
    }

    return 0;
}
```
