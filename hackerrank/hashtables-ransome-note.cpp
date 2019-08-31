```cpp
#include <cstdio>
#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, int> mag;
map<string, int> note;

int main() {
    int m, n;
    string word;
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        cin >> word;
        mag[word] ++;
    }

    bool isDoable = true;

    for (int i = 0; i < n; i++) {
        cin >> word;
        if (isDoable) {
            if (mag.find(word) == mag.end() || mag[word] <= 0) {
                isDoable = false;
            }
        }
        mag[word] --;
    }

    if (isDoable) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}
```
