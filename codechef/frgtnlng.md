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

using namespace std;

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        int n, k;
        scanf("%d%d", &n, &k);

        vector<string> lst;
        map<string, int> m;
        for( int i = 0 ; i < n ; i++ ) {
            string s;
            cin >> s;
            lst.push_back(s);
            m[s] = 0;
        }

        for( int i = 0 ; i < k ; i++ ) {
            int x;
            scanf("%d\n", &x);
            for( int j = 0 ; j < x; j++ ) {
                string ph;
                cin >> ph;
                m[ph] = 1;
            }
        }

        for( vector<string>::iterator itr = lst.begin(); itr != lst.end(); itr++ ) {
            if(m[*itr]) {
                printf("YES ");
            }
            else {
                printf("NO ");
            }
        }
        printf("\n");
    }
    return 0;
}
```
