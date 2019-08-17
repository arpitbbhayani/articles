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
int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while(t--) {
        int n;
        cin >> n;

        ll int sum = 0;
        for(int i = 0 ; i < n ; i++) {
            scanf("%lld", &arr[i]);
            sum += arr[i];
        }

        ll int lsum = 0, rsum;
        int i = 0, count = 0;
        for(i = 1 ; i < n; i++) {
            lsum += arr[i-1];
            rsum = sum - lsum - arr[i];
            if(lsum == rsum) {
                count++;
            }
        }
        if(count || n == 1) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }

    }

    return 0;
}
```
