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

class AscCompare {
public:
    bool operator()(int x, int y) {
        return x > y;
    }
};

priority_queue<int, vector<int>, AscCompare> q;
priority_queue<int> qt;

int main(int argc, char *argv[]) {
    int n, x;
    scanf("%d", &n);

    while(n--) {
        scanf("%d", &x);
        q.push(x);
    }

    while(!q.empty()) {
        cout << q.size() << endl;
        int cut_length = q.top();
        q.pop();

        while(!q.empty()) {
            int temp = q.top();
            temp -= cut_length;

            if(temp > 0) {
                qt.push(temp);
            }
            q.pop();
        }

        while(!qt.empty()) {
            q.push(qt.top());
            qt.pop();
        }
    }

    return 0;
}
