#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int comparator(const void *x , const void *y) {
	int a = *(int *) x;
	int b = *(int *) y;
	return a < b;
}

int main( int argc , char * argv[] ) {

	int t;
	cin >> t;

	while ( t-- ) {
		int n;
		cin >> n;

		int * men = (int *) malloc ( n * sizeof(int) );
		int * women = (int *) malloc ( n * sizeof(int) );

		for ( int i = 0 ; i < n ; i++ )
			scanf("%d" , &men[i] );
		for ( int i = 0 ; i < n ; i++ )
			scanf("%d" , &women[i] );

		qsort( men , n , sizeof(int) , comparator );
		qsort( women , n , sizeof(int) , comparator );

		long long int sum = 0;

		for ( int i = 0 ; i < n ; i++ )
			sum += (men[i] * women[i]);
		
		cout << sum << endl;

		free ( men );
		free ( women );

	}
}
