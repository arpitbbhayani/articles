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
    char array[5][16] = {"BattleShip", "Cruiser", "Destroyer", "", "Frigate"};
    while( t-- ) {
        char str[4], ch;
        scanf("%s", str);
        ch = tolower(str[0]);
        printf("%s\n", array[ch-'b']);
    }
    return 0;
}
```
