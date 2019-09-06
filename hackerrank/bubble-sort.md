```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int arr[601];

int main() {
    int n, swaps = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            if (arr[j] > arr[j+1]) {
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;

                swaps++;
            }
        }
    }

    printf("Array is sorted in %d swaps.\n", swaps);
    printf("First Element: %d\n", arr[0]);
    printf("Last Element: %d\n", arr[n-1]);
    return 0;
}
```
