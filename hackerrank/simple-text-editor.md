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
#include <string.h>

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

stack<string> st;
int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    string s = "";
    string temp;
    while(t--) {
        int q, k;
        scanf("%d", &q);

        switch(q) {
            case 1:
                st.push(s);
                cin >> temp;
                s = s + temp;
                break;
            case 2:
                st.push(s);
                scanf("%d", &k);
                s = s.substr(0, s.length() - k);
                break;
            case 3:
                scanf("%d", &k);
                cout << s[k-1] << endl;
                break;
            case 4:
                s = st.top();
                st.pop();
                break;
        }
    }

    return 0;
}
```
