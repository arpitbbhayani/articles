#include <stdio.h>

int main( int argc , char * argv[] ) {
	int t;
	long long sum , n , m;
 
	scanf("%d",&t);
    
	while( t-- ) {
		scanf("%lld",&n) ;
        
		if( n % 2 == 0 )
			m = n - 3 ;
		else
			m = n - 2 ;
       
		m = (m + 1 )/ 2;
        
		printf("%lld\n", (m * m) % n) ;
	}
    
	return 0 ;
}
