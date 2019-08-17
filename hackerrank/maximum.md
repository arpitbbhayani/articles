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

stack<ll int> s, m;
int main(int argc, char *argv[]) {
    int t, x;
    ll int v, mx = -1;

    scanf("%d", &t);
    while(t--) {
        scanf("%d", &x);
        if(x == 1) {
            scanf("%lld", &v);
            if(mx == -1 || m.empty()) {
                mx = v;
            }
            else {
                mx = MAX(m.top(), v);
            }
            s.push(v);
            m.push(mx);
        }
        else if(x == 2) {
            s.pop();
            m.pop();
        }
        else {
            printf("%lld\n", m.top());
        }
    }

    return 0;
}
