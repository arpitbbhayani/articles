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

int * twoSum(int* nums, int numsSize, int target) {
    int * ans = (int *) malloc(2 * sizeof(int));
    for(int i = 0 ; i < numsSize; i++) {
        for(int j = i + 1; j < numsSize; j++) {
            if(nums[i] + nums[j] == target) {
                ans[0] = i;
                ans[1] = j;
            }
        }
    }
    return ans;
}

int main(int argc, char *argv[]) {
    int * arr = (int *) malloc(4 * sizeof(int));

    arr[0] = 2;
    arr[1] = 7;
    arr[2] = 11;
    arr[3] = 15;

    int * t = twoSum(arr, 4, 9);
    printf("%d %d\n", t[0], t[1]);

    return 0;
}
```
