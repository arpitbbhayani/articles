```cpp
#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

long long int arr[100001];
map<long long int, long long int> map_c, map_b;

int main() {
    long long int count = 0;
    long long int n, r;

    scanf("%lld %lld", &n, &r);
    for (int i = 0 ; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    // here a number can be an A or a B or a C from
    // Geometric progression triplet (A, B, C) with
    // ratio r.
    for (int i = 0; i < n; i++) {
        // number is a C the update the final count
        count += map_c[arr[i]];

        // number is a B
        // add number of Bs that exist into into Cs
        map_c[arr[i] * r] += map_b[arr[i]];

        // number is an A
        // this means add the count of it being B
        map_b[arr[i] * r]++;
    }

    printf("%lld\n", count);
    return 0;
}
```
