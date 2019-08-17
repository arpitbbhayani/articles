```c
#include <stdio.h>
 
int jo(int n, int k) {
	int ans = 0, i;
	for(i = 2; i <= n; i++) ans = (ans + k) % i;
	return ans+1;
}
 
int main() {
	int n , k;
	scanf("%d%d" , &n , &k);
	while ( n != 0 && k != 0 ) {
		printf("%d %d %d\n", n , k , jo(n, k));
		scanf("%d%d" , &n , &k);
	}
	return 0;
}
```
