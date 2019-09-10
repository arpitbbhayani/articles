```cpp
#include <cstdio>
#include <iostream>

using namespace std;

int arr[100001];
int temp[100001];

long long int merge(int start, int mid, int end) {
    long long int count = 0;
    int i = start, j = mid, index = start;
    while (i <= (mid - 1) && j <= end) {
        if (arr[i] <= arr[j]) {
            temp[index++] = arr[i++];
        } else {
            temp[index++] = arr[j++];
            count += (mid - i);
        }
    }

    while (i <= mid - 1) {
        temp[index++] = arr[i++];
    }

    while (j <= end) {
        temp[index++] = arr[j++];
    }

    for (int i = start; i <= end ; i++) {
        arr[i] = temp[i];
    }

    return count;
}

long long int sort(int start, int end) {
    if (start >= end) {
        return 0;
    }

    long long int count = 0;
    int mid = start + (end-start)/2;
    count += sort(start, mid);
    count += sort(mid + 1, end);
    count += merge(start, mid + 1, end);
    return count;
}

long long int count_inv(int n) {
    return sort(0, n - 1);
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n ; i++) {
            scanf("%d", &arr[i]);
        }
        printf("%lld\n", count_inv(n));
    }
    return 0;
}
```
