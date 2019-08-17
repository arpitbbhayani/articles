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

int h1[220];
int h2[220];

int main(int argc, char *argv[]) {
    int n, m, x;
    int base;

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
        if(i == 0) {
            base = x;
        }
        h1[100 + (x - base)]++;
    }

    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &x);
        h2[100 + (x - base)]++;
    }

    vector<int> y;
    for(int i = 0 ; i < 220; i++) {
        int d = (h2[i] - h1[i]);
        if(d > 0) {
            y.push_back(i + base - 100);
        }
    }

    for(vector<int>::iterator itr = y.begin(); itr != y.end(); itr++) {
        cout << *itr << " ";
    }
    cout << endl;

    return 0;
}
```
