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

int arr[1010];
int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);

    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    }

    int sum = 0;
    for(int i = 0 ; i < n ;i++) {
        sum += arr[i];
    }

    if(sum & 1) {
        printf("NO\n");
    }
    else {
        int count = 0;
        for(int i = 0 ; i < (n-1) ; i++) {
            if(arr[i] & 1) {
                arr[i]++;
                arr[i+1]++;
                count += 2;
            }
        }
        cout << count << endl;
    }

    return 0;
}
