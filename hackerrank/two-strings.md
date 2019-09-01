```cpp
#include <cstdio>
#include <iostream>

using namespace std;

char str[100005];

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int a[256] = {}, is_substr = false;
        scanf("%s", str);

        for (int i = 0; str[i]; i++) {
            a[str[i]] = 1;
        }

        scanf("%s", str);
        for (int i = 0; is_substr == false && str[i]; i++) {
            is_substr = a[str[i]];
        }

        printf("%s\n", is_substr ? "YES" : "NO");
    }

    return 0;
}
```
