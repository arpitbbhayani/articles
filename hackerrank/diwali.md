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

int l = 10005;
int arr[10010];

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    arr[0] = 1;
    for(int i = 1; i < l; i++) {
        arr[i] = (arr[i-1] << 1) % 100000;
    }

    while(t--) {
        int n;
        cin >> n;
        cout << arr[n] - 1 << endl;
    }

    return 0;
}
