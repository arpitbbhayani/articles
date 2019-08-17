```
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

int process(int * arr, int n) {
    int swaps = 0;
    int * count = (int *) calloc(n + 1, sizeof(int));
    while(1) {
        int change = 0;
        for(int i = 0 ; i < n - 1; i++) {
            if(arr[i] > arr[i+1] && count[arr[i]] < 2) {
                swaps++;
                change = 1;
                count[arr[i]]++;
                int t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
            }
        }

        if(change == 0) {
            int i = 0;
            for(i = 0 ; i < n - 1; i++) {
                if(arr[i] > arr[i+1]) {
                    return -1;
                }
            }

            if(i == n - 1) {
                return swaps;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while(t--) {
        int n;
        cin >> n;
        int * arr = (int *) calloc(n, sizeof(int));

        for(int i = 0 ; i < n ; i++) {
            scanf("%d", &arr[i]);
        }

        int ans = process(arr, n);
        if(ans == -1) {
            printf("Too chaotic\n");
        }
        else {
            printf("%d\n", ans);
        }

        free(arr);
    }

    return 0;
}
```
