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

int compar(const void * a, const void * b) {
    unsigned ll *x = (unsigned ll int *) (a);
    unsigned ll *y = (unsigned ll int *) (b);
    return (*x) > (*y);
}

int main(int argc, char *argv[]) {

    unsigned ll int *arr;
    arr = (unsigned ll int *) malloc(5 * sizeof(unsigned ll int));
    for(int i = 0 ; i < 5; i++) {
        cin >> arr[i];
    }

    qsort(arr, 5, sizeof(unsigned ll int), compar);

    unsigned ll int min_sum = 0;
    unsigned ll int max_sum = 0;

    for(int i = 1 ; i < 5; i++) {
        max_sum += arr[i];
    }

    for(int i = 0 ; i < 4; i++) {
        min_sum += arr[i];
    }

    cout << min_sum << " " << max_sum << endl;

    free(arr);
    return 0;
}
