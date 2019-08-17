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


char arr[501][501];
int main(int argc, char *argv[]) {
    int n, m;
    scanf("%d%d", &n, &m);
    getchar();
    for(int i = 0 ; i < n ; i++) {
        scanf("%s", arr[i]);
    }

    int count = 0;
    int max_count = -1;
    for(int i = 0; i < n ; i++) {
        for(int j = i + 1; j < n; j++) {
            int local_count = 0;
            for(int k = 0; k < m; k++) {
                local_count += ((arr[i][k] - '0') | (arr[j][k] - '0'));
            }
            if(local_count > max_count) {
                max_count = local_count;
                count = 0;
            }

            if(local_count == max_count) {
                count++;
            }
        }
    }
    printf("%d\n%d\n", max_count, count);
    return 0;
}
```
