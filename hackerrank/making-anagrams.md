```cpp
#include <cstdio>
#include <iostream>

using namespace std;

char str[10010];
int counts[256];

int main() {
    int count = 0;
    
    scanf("%s", str);
    for (int i = 0; str[i]; i++) {
        counts[str[i]]++;
    }
    scanf("%s", str);
    for (int i = 0; str[i]; i++) {
        counts[str[i]]--;
    }

    for (int i = 0; i < 256; i++) {
        count += counts[i] < 0 ? -counts[i] : counts[i];
    }
    printf("%d\n", count);
    return 0;
}
```
