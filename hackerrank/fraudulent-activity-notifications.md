```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int arr[200010];
int temp_arr[200010];
int counts[210];

float get_median(int size) {
    int index = 0;
    for (int i = 0; i < 210 ; i++) {
        int count = counts[i];
        while (count--) {
            temp_arr[index++] = i;
            if (index > size/2) { break; }
        }
        if (index > size/2) { break; }
    }
    return size % 2 == 1 ? temp_arr[size/2] : (temp_arr[size/2] + temp_arr[size/2-1])/2.0;
}

int main() {
    int n, d;

    scanf("%d %d", &n, &d);
    for (int i = 0; i < n ; i++) {
        scanf("%d", &arr[i]);
    }

    int alarm_count = 0;
    float median = 210;

    for (int i = 0; i < d ; i++) {
        counts[arr[i]]++;
    }
    median = get_median(d);

    for (int i = d; i < n; i++) {
        if (arr[i] >= 2*median) {
            alarm_count++;
        }

        // update counts array
        counts[arr[i-d]]--;
        counts[arr[i]]++;

        median = get_median(d);
    }

    printf("%d\n", alarm_count);
    return 0;
}
```
