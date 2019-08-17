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

map<ll int, ll int> m;
ll int arr[100001];
int main(int argc, char *argv[]) {
    ll int n, k;
    scanf("%lld%lld", &n, &k);

    for(int i = 0 ; i < n ; i++) {
        cin >> arr[i];
        if(arr[i] % k == 0) {
            m[arr[i] % k] = 1;
        }
        else {
            m[arr[i] % k]++;
        }
    }

    ll int count = m[0];
    ll int start = 1;
    ll int end = k - 1;
    while(start < end) {
        count += MAX(m[start], m[end]);
        start++;
        end--;
    }

    if(k % 2 == 0 && m.find(k/2) != m.end()) {
        count++;
    }

    printf("%lld\n", count);

    return 0;
}
