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
#include <algorithm>

#define ll long long

#define MIN(a, b) a < b ? a : b

using namespace std;

bool pairCompare(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.second > b.second;
}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    char ans[2][8] = {"YES", "NO"};

    while( t-- ) {
        char str[64];
        scanf("%s", str);

        int * hash = (int *)calloc(26 , sizeof(int));
        for(int i = 0 ; str[i]; i++ ) {
            hash[str[i] - 'a']++;
        }

        vector< pair<int, int> > l;
        for(int i = 0 ; i < 26; i++ ) {
            l.push_back(make_pair(i, hash[i]));
        }

        sort(l.begin(), l.end(), pairCompare);

        int count = (l.begin()->second);
        for(vector<pair <int, int> >::iterator itr = (l.begin())+1; itr != l.end(); itr ++) {
            //printf("%c %d\n", (char)(itr->first + 'a'), itr->second);
            count -= itr->second;
        }

        if(count){count = 1;};
        printf("%s\n", ans[count]);
    }
    return 0;
}
```
