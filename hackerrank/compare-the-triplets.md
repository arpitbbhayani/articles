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

int main(int argc, char *argv[]) {
    int a[3], b[3];

    for(int i = 0 ; i < 3; i++) {
        cin >> a[i];
    }

    for(int i = 0 ; i < 3; i++) {
        cin >> b[i];
    }

    int pa = 0, pb = 0;
    for(int i = 0; i < 3; i++) {
        if(a[i] > b[i]) {
            pa++;
        }
        else if(a[i] < b[i]) {
            pb++;
        }
    }

    cout << pa << " " << pb << endl;

    return 0;
}
```
