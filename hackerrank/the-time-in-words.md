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

char nstr[31][32] = {"", "one", "two", "three", "four", "five", "six",
                     "seven", "eight", "nine", "ten", "eleven", "twelve",
                     "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                     "eighteen", "nineteen", "twenty", "twenty one",
                     "twenty two", "twenty three", "twenty four",
                     "twenty five", "twenty six", "twenty seven",
                     "twenty eight", "twenty nine", "half"};

int main(int argc, char *argv[]) {
    int h, m;
    scanf("%d%d", &h, &m);

    if(m == 0) {
        printf("%s o' clock", nstr[h]);
    } else if(m == 1) {
        printf("%s minute past %s", nstr[m], nstr[h]);
    } else if(m == 15) {
        printf("quarter past %s", nstr[h]);
    } else if(m < 30) {
        printf("%s minutes past %s", nstr[m], nstr[h]);
    } else if(m == 30) {
        printf("%s past %s", nstr[m], nstr[h]);
    } else if(m == 59) {
        h++;
        if(h == 13) { h = 1; }
        printf("%s minute to %s", nstr[m], nstr[h]);
    } else if(m == 45) {
        h++;
        if(h == 13) { h = 1; }
        printf("quarter to %s", nstr[h]);
    } else if(m > 30) {
        h++;
        if(h == 13) { h = 1; }
        m = 60 - m;
        printf("%s minutes to %s", nstr[m], nstr[h]);
    }

    printf("\n");
    return 0;
}
```
