```
#include <iostream>
#include <cstdio>

using namespace std;

int s( long long int n , long long int m ) {
	int q = (n-m)&((m-1)/2);
	if ( q == 0 )
		return 1;
	else
		return 0;
}

int main ( int argc , char * argv[] ) {

	long long int n , m , t;

	scanf("%lld" , &t);

	while ( t-- ) {

		scanf("%lld%lld" , &n , &m);

		cout << s(n,m) << endl;

		/*for ( int i = 1 ; i < n+1 ; i++ ) {
			for ( int j = 1 ; j < m+1 ; j++ ) {
				array[i][j] = (j * array[i-1][j] + array[i-1][j-1])&1;
			}
		}*/

		/*for ( int i = 0 ; i < n+1 ; i++ ) {
			for ( int j = 0 ; j < m+1 ; j++ ) {
				cout << array[i][j] << " ";
			}
			cout << endl;
		}*/

	}

	return 0;
}
```
