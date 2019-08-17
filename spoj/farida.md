```
#include <iostream>

using namespace std;

int main ( int argc , char * argv[] ) {

	int t;
	long long int sum[10010] , max_ = 0;

	cin >> t;

	for(int l = 0 ; l < t ; l++ ) {

		int n;
		cin >> n ;

		for ( int i = 0 ; i < n ; i++ ) {
			cin >> sum[i];
		}

		if ( n == 1 ) {
			max_ = sum[n-1];
		}
		else {
			sum[1] = max(sum[0] , sum[1]);

			for ( int i = 2 ; i < n ; i++ ) {

				long long int sum_y = sum[i-2] + sum[i];
				long long int sum_n = sum[i-1];
				sum[i] = max ( sum_y , sum_n );
			}
			//for ( int i = 0 ; i < n ; i++ ) {
			//	cout << " " << sum[i];
			//}
			max_ = sum[n-1];
		}
		
		cout << "Case " << l+1 << ": " << max_ << endl;

	}
	

	return 0;
}
```
