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

void reverse_array(int * array, int length) {
    int start = 0, end = length - 1;
    while(start < end) {
        int t = array[start];
        array[start] = array[end];
        array[end] = t;
        start++;
        end--;
    }
}

void print_array(int * array, int length) {
    for(int i = 0; i< length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int n, k, q;
    int array[100010];
    scanf("%d%d%d", &n, &k, &q);

    for(int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    k = k % n; // in case rotations are more than n

    while(q--) {
        int x;
        scanf("%d", &x);

        if(x - k >= 0) {
            printf("%d\n", array[x - k]);
        }
        else {
            printf("%d\n", array[n + x - k]);
        }

    }

    return 0;
}
