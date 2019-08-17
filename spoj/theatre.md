#include <iostream>
#include <cstdio>
#include <stack>
#include <cstdlib>

using namespace std;

int main ( int argc , char * argv[] ) {

	int n;
	int *a;
	stack<int> s;

	scanf("%d" , &n );

	a = (int *) malloc( n * sizeof(int));

	for ( int i = 0 ; i < n ; i++ ) {
		scanf("%d" , &a[i]);
	}

	if ( n == 1 ) {
		printf("1\n");
		return 0;
	}

	s.push(a[n-1]);
	long long int ans = 1;
	for ( int i = n-2; i >= 0 ; i-- ) {
		if ( a[i] > s.top() ) {
			
			while ( !s.empty() && a[i] > s.top() )
				s.pop();
			if ( s.empty() ) {
			}
			else {
				ans = (ans * s.top()) % 1000000007;
			}
			s.push(a[i]);
			
		}
		else if ( a[i] < s.top() ) {
			if ( s.empty() ) {
			}
			else {
				ans = (ans * s.top()) % 1000000007;
			}
			s.push(a[i]);
		}
	}
	printf("%lld\n" , ans);

	free(a);

	return 0;
}
