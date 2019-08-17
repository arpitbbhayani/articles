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

int arr[26];
int main(int argc, char *argv[]) {
    char str[16];
    for(int i = 0; i < 26; i++) {
        scanf("%d", &arr[i]);
    }
    getchar();
    int l = readline(str);

    int m = INT_MIN;
    for(int i = 0; str[i]; i++) {
        m = MAX(m, arr[str[i] - 'a']);
    }
    printf("%d\n", m * l);
    return 0;
}
```
