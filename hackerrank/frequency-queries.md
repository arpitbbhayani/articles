```cpp
#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

map<long long int, long long int> m;
map<long long int, long long int> f;
int main() {
    long long int n;
    scanf("%lld", &n);
    while (n--) {
        long long int a, b;
        scanf("%lld %lld", &a, &b);

        switch (a) {
            case 1:
                if (f[m[b]] > 0) {
                    f[m[b]]--;
                }
                m[b]++;
                f[m[b]]++;
                break;
            case 2:
                if (f[m[b]] > 0) {
                    f[m[b]]--;
                }
                if (m[b] > 0) {
                    m[b]--;
                }
                f[m[b]]++;
                break;
            case 3:
                printf("%d\n", f.count(b) && f[b] > 0);
                break;
        }
    }
    return 0;
}
```
