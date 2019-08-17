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

char large[1002][1002];
char small[1002][1002];

int main(int argc, char *argv[]) {
    int t;

    scanf("%d", &t);
    while(t--) {
        int r1, c1;
        scanf("%d%d", &r1, &c1);
        for(int i = 0; i < r1; i++) {
            scanf("%s", large[i]);
        }

        int r2, c2;
        scanf("%d%d", &r2, &c2);
        for(int i = 0; i < r2; i++) {
            scanf("%s", small[i]);
        }

        int is_match = 0;
        for(int i = 0 ; i < r1 && is_match == 0; i++) {
            for(int j = 0; j < c1 && is_match == 0; j++) {
                is_match = 0;
                char ch = large[i][j];

                if(ch == **small) {
                    int k, l;

                    for(k = 0; k < r2 && is_match == 0; k++) {
                        for(l = 0; l < c2 && is_match == 0; l++) {
                            if(i + k >= r1 || j + l >= c1) {
                                is_match = 0;
                                k = r2 + 1;
                                break;
                            }
                            if(small[k][l] != large[i + k][j + l]) {
                                is_match = 0;
                                k = r2 + 1;
                                break;
                            }

                        }
                    }

                    if(k == r2 && l == c2) {
                        is_match = 1;
                    }
                }
            }
        }

        if(is_match == 1) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }

    }


    return 0;
}
```
