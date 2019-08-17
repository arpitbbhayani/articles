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

int main(int argc, char *argv[]) {
    char s[110];
    ll int n;
    ll int l = readline(s);
    scanf("%lld", &n);

    ll int count_a = 0, i = 0;
    ll int count = 0;
    for(i = 0 ; s[i]; i++) {
        if(s[i] == 'a') {
            count_a++;
        }
    }

    count += ((n / l) * count_a);
    for(i = 0; i < (n % l); i++) {
        if(s[i] == 'a') {
            count++;
        }
    }

    printf("%lld\n", count);

    return 0;
}
```
