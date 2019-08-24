```c
#include <stdio.h>

int countingValleys(int n, char* s) {
    int level = 0, count = 0;
    for(int i = 0; s[i]; i++) {

        int prevLevel = level;

        if (s[i] == 'U') {
            level ++;
        } else {
            level --;
        }

        if (level < 0 && prevLevel >= 0) {
            count ++;
        }
    }
    return count;
}

int main()
{
    int n;
    char str[1000001];

    scanf("%d", &n);
    scanf("%s", str);

    printf("%d\n", countingValleys(n, str));

    return 0;
}
```
