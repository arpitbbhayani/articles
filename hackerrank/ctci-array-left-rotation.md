```c
#include <stdio.h>

int arr[100010];

void reverse(int start, int end) {
    int t;
    while (start < end) {
        t = arr[start];
        arr[start] = arr[end];
        arr[end] = t;

        start++;
        end--;
    }
}

void rotate_left(int n, int k) {
    reverse(0, k-1);
    reverse(k, n-1);
    reverse(0, n-1);
    return;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    rotate_left(n, k);

    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
```
