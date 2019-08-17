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

using namespace std;

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {
        char str1[110], str2[110];
        scanf("%s%s", str1, str2);

        int ansmin = 0;
        int ansmax = 0;
        int q1 = 0, q2 = 0;
        int compulsory_same = 0, compulsory_diff = 0;
        int i = 0;
        for(i = 0 ; str1[i] ; i++ ) {
            char ch1 = str1[i], ch2 = str2[i];

            if(ch1 == '?') {
                q1++;
            }

            if(ch2 == '?') {
                q2++;
            }

            if(ch1 != '?' && ch2 != '?' && ch1 != ch2) {
                compulsory_diff++;
            }

            if(ch1 != '?' && ch2 != '?' && ch1 == ch2) {
                compulsory_same++;
            }
        }
        ansmin = compulsory_diff;
        ansmax = i - compulsory_same;
        printf("%d %d\n", ansmin, ansmax);
    }
    return 0;
}
```
