#include <stdio.h>

int main ( int argc , char  *argv[] ) {

	double sum = 0;
	double n;

	scanf("%lf" , &n);

	while ( n != 0 ) {
		double i = 2;
		for ( i = 2 , sum = 0 ; sum <= n ; i++ ) {
			sum += 1/i;
		}

		printf("%d card(s)\n" , ((int) i) - 2);
		scanf("%lf" , &n);

	}

	return 0;
}
