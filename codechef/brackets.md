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

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while( t-- ) {

        char str[100010];
        scanf("%s", str);

        int balance = 0;
        int max_balance = 0;
        for( int i = 0 ; str[i]; i++ ) {
            if(str[i] == '(') {
                balance ++;
            }
            else {
                balance --;
            }
            max_balance = MAX(max_balance, balance);
        }

        for(int i = 0 ; i < max_balance; i++) {
            printf("(");
        }
        for(int i = 0 ; i < max_balance; i++) {
            printf(")");
        }
        printf("\n");

    }
    return 0;
}
```
