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

ll int gcd(ll int a, ll int b) {
  if(b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);

    while(t--) {
      ll int l, b, g;
      cin >> l >> b;

      ll int t;
      if(l < b) {
          t = l;
          l = b;
          b = t;
      }

      g = gcd(l, b);
      cout << (l / g) * (b / g) << endl;
    }

    return 0;
}
