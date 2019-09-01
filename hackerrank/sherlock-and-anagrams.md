```cpp
#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

int primes[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
    41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

map<int, int> occurances;
long long int BIG_PRIME = 1000000007;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        char str[110];
        long long int count = 0;
        scanf("%s", str);

        occurances.clear();

        for (int i = 0; str[i]; i++) {
            long long int unique_key = 1;
            for (int j = i; str[j]; j++) {
                unique_key = (unique_key * primes[str[j] - 'a']) % BIG_PRIME;

                // occurances will hold count of anagamic substrings
                occurances[unique_key]++;
            }
        }

        for (map<int, int>::iterator itr = occurances.begin(); itr != occurances.end(); itr++) {
            // since we need to find pairs
            // we find number of ways in which we pick 2 from #occurances
            count += ((itr->second * (itr -> second - 1))/2);
        }

        printf("%lld\n", count);
    }
    return 0;
}
```
