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
    char *s = (char *) malloc(110 * sizeof(char));
    char *t = (char *) malloc(110 * sizeof(char));
    int chances;

    int ls = readline(s);
    int lt = readline(t);
    scanf("%d", &chances);

    int i = 0;
    while(s[i] && t[i]) {
        if(s[i] != t[i]) {
            break;
        }
        i++;
    }
    int prefix_length = i;
    int is_possible;

    if(chances >= (lt + ls)) {
        printf("Yes\n");
        return 0;
    }

    chances -= abs(lt - prefix_length);
    chances -= abs(ls - prefix_length);

    if(chances < 0) {
        printf("No\n");
        return 0;
    }

    if(chances % 2 == 0) {
        printf("Yes\n");
        return 0;
    }

    printf("No\n");
    return 0;
}


/*
 *  Code for better Understanding
 */


/*
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
    char *s = (char *) malloc(110 * sizeof(char));
    char *t = (char *) malloc(110 * sizeof(char));
    int chances;

    int ls = readline(s);
    int lt = readline(t);
    scanf("%d", &chances);

    int i = 0;
    while(s[i] && t[i]) {
        if(s[i] != t[i]) {
            break;
        }
        i++;
    }
    int prefix_length = i;
    int is_possible;

    if(chances >= (lt + ls)) {
        printf("Yes\n");
        return 0;
        // When chances I have are greater than target length + source_length.
        // Then it is always possible to construct t from s.
    }

    int target_length = abs(lt - prefix_length);
    int source_length = abs(ls - prefix_length);

    if(target_length > source_length) {
        // aaba
        // aabcde
        chances -= (source_length); // deleting 1 char from s
        chances -= (target_length); // adding 3 chars to s
    }
    else if(target_length < source_length) {
        // aabcde
        // aaba
        chances -= (source_length); // deleting 3 chars from s
        chances -= (target_length); // adding 1 char to s
    }
    else {
        // aabcde
        // aadefg
        chances -= (source_length); // deleting 3 chars from s
        chances -= (target_length); // adding 3 chars to s
    }

    if(chances < 0) {
        is_possible = 0;
    }
    else if(chances % 2 == 0) {
        is_possible = 1;
    }
    else {
        is_possible = 0;
    }

    if(is_possible) {
        printf("Yes\n");
    }
    else {
        printf("No\n");
    }

    return 0;
}

*/
```
