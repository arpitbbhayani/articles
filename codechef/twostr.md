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
    char ans[2][10] = {"No", "Yes"};
    while( t-- ) {
        char str1[100], str2[100];
        scanf("%s%s", str1, str2);

        int is_matched = 1;
        for(int i = 0 ; str1[i]; i++ ) {
            char ch1 = str1[i], ch2 = str2[i];
            if( (ch1 != ch2) && (ch1 != '?' && ch2 != '?') ) {
                is_matched = 0;
            }
        }
        printf("%s\n", ans[is_matched]);
    }
    return 0;
}
```
