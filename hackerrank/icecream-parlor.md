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

int arr[100010];
map<int, vector<int> > m;
int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while(t--) {
        m.clear();
        int sum, n;
        scanf("%d%d", &sum, &n);
        for(int i = 1 ; i <= n; i++) {
            scanf("%d", &arr[i]);
            m[arr[i]].push_back(i);
        }

        int ans1 = 0, ans2 = 0;
        for(int i = 1; i <= n; i++) {
            int vala = arr[i];
            int valb = sum - arr[i];
            vector<int> indexa, indexb;

            map<int, vector<int> >::iterator itra = m.find(vala);
            map<int, vector<int> >::iterator itrb = m.find(valb);

            if(itra != m.end() && itrb != m.end()) {
                indexa = itra->second;
                indexb = itrb->second;
                if(vala == valb && indexa.size() >= 2) {
                    ans1 = indexa[0];
                    ans2 = indexa[1];
                    break;
                }
                else if(vala == valb && indexa.size() < 2) {
                    // Nothing
                }
                else if(vala != valb) {
                    ans1 = indexa[0];
                    ans2 = indexb[0];
                    break;
                }
            }
        }

        if(ans1 > ans2) {
            int t = ans1;
            ans1 = ans2;
            ans2 = t;
        }
        printf("%d %d\n", ans1, ans2);
    }

    return 0;
}
```
