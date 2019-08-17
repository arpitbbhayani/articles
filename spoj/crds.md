```
#include <stdio.h>
#define MOD 1000007
int main ( void ) {

	int t;
	scanf("%d" , &t);
	while ( t-- ) {
		long long int n;
		scanf("%lld" , &n);
		long long int ans = ((n*(3*n+1))/2);
		ans %= MOD;
		printf("%lld\n" , ans);
	}
	return 0;
}
```
