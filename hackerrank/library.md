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

    int sd, sm, sy;
    int dd, dm, dy;

    cin >> sd >> sm >> sy >> dd >> dm >> dy;

    int fine = 0;

    if(dy == sy) {
        if(sm > dm) {
            fine = (sm - dm) * 500;
        }
        else if(sm == dm && sd > dd) {
            fine = (sd - dd) * 15;
        }
    }
    else if(sy > dy) {
        fine = 10000;
    }
    cout << fine << endl;
    return 0;
}
