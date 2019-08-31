```cpp
#include <cstdio>
#include <iostream>

long long int arr[10000010];

int main() {
    int n, t;
    int a, b;
    long long int k;

    scanf("%d %d", &n, &t);

    for (int i = 0; i < t; i++) {
        scanf("%d %d %lld", &a, &b, &k);
        arr[a] += k;
        arr[b+1] -= k;
    }

    long long int max = INT64_MIN, sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += arr[i];        
        max = sum > max ? sum : max;
    }
    printf("%lld\n", max);
    return 0;
}
```
