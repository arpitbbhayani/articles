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

int safe(int i, int j, int row, int col) {
    if(i >= 0 && j >= 0 && i < row && j < col) {
        return 1;
    }
    return 0;
}

void dfs(int **grid, int i, int j, int row, int col, int ** visited) {
    if(visited[i][j] == 1) {
        return;
    }

    int arrx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    int arry[8] = {0, 0, 1, -1, 1, -1, 1, -1};

    visited[i][j] = 1;
    for(int l = 0; l < 8; l++) {
        int ni = i + arrx[l];
        int nj = j + arry[l];

        if(safe(ni, nj, row, col) && grid[ni][nj] == 1) {
            dfs(grid, ni, nj, row, col, visited);
        }
    }
}

int numIslands(int** grid, int gridRowSize, int gridColSize) {
    int row = gridRowSize, col = gridColSize;

    int ** visited = (int **) calloc(row, sizeof(int *));
    for(int i = 0 ; i < row ; i++) {
        visited[i] = (int *) calloc(col, sizeof(int));
    }

    int count = 0;
    for(int i = 0 ; i < row; i++) {
        for(int j = 0 ; j < col; j++) {
            if(visited[i][j] == 0 && grid[i][j] == 1) {
                dfs(grid, i, j, row, col, visited);
                count++;
            }
        }
    }

    for(int i = 0 ; i < row ; i++) {
        free(visited[i]);
    }
    free(visited);
    return count;
}

int main(int argc, char *argv[]) {
    int row, col;
    scanf("%d%d", &row, &col);

    int **grid = (int **) malloc(row * sizeof(int *));
    for(int i = 0 ; i < row ; i++) {
        grid[i] = (int *) malloc((col + 1) * sizeof(int));
    }

    for(int i = 0 ; i < row ; i++) {
        for(int j = 0 ; j < col; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    printf("%d\n", numIslands(grid, row, col));
    return 0;
}
