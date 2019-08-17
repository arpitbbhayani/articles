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

int arr[101];

int main(int argc, char *argv[]) {
    int n, k;
    scanf("%d%d", &n, &k);

    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    }

    int count = 0;
    for(int j = 0 ; j < n ; j++) {
        for(int i = 0 ; i < j; i++) {
            if((arr[i] + arr[j]) % k == 0) {
                count++;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}
```
