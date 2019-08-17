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

int npow(int a, int b) {
    if(b == 0) {
        //printf(" pow = %d - B\n", 1);
        return 1;
    }
    //printf(" pow = %d - C\n", (a & 1) ? 1 : 2);
    return (a & 1) ? 1 : 2;
}

int main(int argc, char *argv[]) {
    int n, q;
    int x, y;
    char result[4][8] = {"Even", "Odd"};

    scanf("%d", &n);
    for(int i = 1; i <= n ; i++ ) {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &q);

    while(q--) {
        int ans;

        scanf("%d%d", &x, &y);

        if(x < n && arr[x + 1] == 0 && x != y ) {
            // Since the value just after "x"th index is 0
            // so no matter what ans will be 1 -> odd
            ans = 1;
        }
        else {
            // In all other cases the odd/even of base determines
            // the odd/even of result
            ans = arr[x];
        }

        printf("%s\n", result[ans & 1]);
    }

    return 0;
}
```
