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

int _gcd(int a, int b) {
    if(b == 0) {
        return a;
    }
    return _gcd(b, a % b);
}

int gcd(int a, int b) {
    if(a > b) {
        return _gcd(a, b);
    }
    return _gcd(b, a);
}

int lcm_2(int a, int b) {
    return (int) ((ll int)(a) * (ll int)(b)) / gcd(a, b);
}

int lcm(int * arr, int n) {
    int l = 1;
    for(int i = 0 ; i < n; i++) {
        l = lcm_2(arr[i], l);
    }
    return l;
}

int main(int argc, char *argv[]) {
    int n, m;
    int *arr1, *arr2;
    scanf("%d%d", &n, &m);

    arr1 = (int *) malloc(sizeof(int) * n);
    arr2 = (int *) malloc(sizeof(int) * m);

    for(int i = 0 ; i < n; i++) {
        scanf("%d", &arr1[i]);
    }

    int minb = INT_MAX;
    for(int i = 0 ; i < m; i++) {
        scanf("%d", &arr2[i]);
        minb = (arr2[i] < minb) ? arr2[i] : minb;
    }

    int lcma, count = 0;

    lcma = lcm(arr1, n);

    for(int i = lcma; i <= minb; i+= lcma) {
        int all_check = 1;
        for(int j = 0; j < m; j++) {
            if(arr2[j] % i != 0) {
                all_check = 0;
            }
        }
        count += all_check;
    }
    printf("%d\n", count);

    free(arr1);
    free(arr2);

    return 0;
}
