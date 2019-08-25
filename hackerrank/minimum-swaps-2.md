```cpp
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>

using namespace std;

int arr[100010];
map<int, int> visited;

int dfs(int _index) {
    int count = 0, index = _index;

    while (visited[index] == 0) {
        visited[index] = 1;
        count += 1;
        index = arr[index];
    }

    return count - 1;
}

int swap_count(int n) {
    int count = 0;
    for(int i = 1; i <= n; i++) {
        if (visited[i] == 1) {
            continue;
        }
        count += dfs(i);
    }
    return count;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("%d\n", swap_count(n));
    return 0;
}
```
