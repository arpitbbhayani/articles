```c
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
    int t;
    scanf("%d", &t);

    while(t--) {
        ll int n, a, b;
        cin >> n >> a >> b;

        set<int> s;
        n--;
        for (int i = 0; i <= n; i++) {
            s.insert(i * b + (n - i) * a);
        }

        for (set<int>::iterator itr = s.begin(); itr != s.end(); itr++) {
            cout << *itr << " ";
        }
        cout << endl;
    }

    return 0;
}
```
