#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#define inf 1000000000
#define MAXN 50000

using namespace std;

int niz[MAXN];
int n;
bool distribute_candies(int candies_per_person, int persons) {
    for (int i = 0; i < n; ++i) {
        persons -= niz[i] / candies_per_person;
        if (persons < 1) return true;
    }
    return false;
}

int main()
{
    int t;
    scanf("%d", &t);
    
    for (int qwertz = 0; qwertz < t; ++qwertz) {
        int k;
        scanf("%d%d", &n, &k);
        
        memset(niz, 0, sizeof niz);
        
        int max = -inf;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &niz[i]);
            if (niz[i] > max) max = niz[i];
        }
        
        int lo = 0, hi = max;
        while (lo < hi) {
            int mid = lo + (hi - lo + 1) / 2;
            if (distribute_candies(mid, k)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        
        printf("%d\n", lo);
    }
    
    return 0;
}
