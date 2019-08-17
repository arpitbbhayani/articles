/*
 *  Author: Arpit Bhayani
 *  https://arpitbhayani.me
 */
#include <cmath>
#include <cstdio>
#include <cstring>
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

char str[100];
char arr[10][10];
int main(int argc, char *argv[]) {
    int index = 0;
    scanf("%s", str);
    int len = strlen(str);
    int cols = sqrt(len);

    if(cols * cols != len) {
        cols++;
    }

    for(int i = 0 ; str[index] ; i++) {
        for(int j = 0 ; j < cols && str[index]; j++) {
            arr[i][j] = str[index++];
        }
    }

    for(int j = 0 ; j < cols; j++) {
        for(int i = 0 ; arr[i][j]; i++) {
            printf("%c", arr[i][j]);
        }
        printf(" ");
    }

    printf("\n");

    return 0;
}
