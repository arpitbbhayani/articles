```cpp
#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

char str[100010];
int counts[26];
map<int, int> m;

int main() {
    scanf("%s", str);
    for (int i = 0 ; str[i] ; i++) {
        int index = str[i] - 'a';
        counts[index]++;
    }

    for (int i = 0; i < 26 ; i++) {
        if (counts[i] > 0) {
            m[counts[i]]++;
        }
    }

    if (m.size() == 1) {
        printf("YES\n");
    } else if (m.size() == 2) {
        int max_chars = -1, min_chars = INT32_MAX;
        map<int, int> num_chars_to_freq;
        for (map<int, int>::iterator itr = m.begin() ; itr != m.end() ; itr++) {
            num_chars_to_freq[itr->second] = itr->first;
            max_chars = itr->second > max_chars ? itr->second : max_chars;
            min_chars = itr->second < min_chars ? itr->second : min_chars;
        }

        if (num_chars_to_freq.size() == 1) {
            printf("NO\n");
            return 0;
        }

        if (num_chars_to_freq[min_chars] - num_chars_to_freq[max_chars] == 1) {
            printf("YES\n");
        } else if (num_chars_to_freq[min_chars] == 1 && min_chars == 1) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }

    } else {
        printf("NO\n");
    }

    return 0;
}
```
