/**
 *	Total money transfer is the sum of all the money
 *	Net flow is the minimum transfer that is to be done
 *	This minimum transfer will be the one that has to be done
 *	which can be calculated using
 *	For each bank the minimum transfer that needs to be done
 *	will be the extra money that it has
 *	i.e. outflow for each bank - inflow for each bank
 *	This amount will be the one that is spare with the bank and
 *	will be transfering it to other bank
 *	so 
 *	Summation of (outflow-inflow) is the answer
 */


#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

int readline ( char * str ) {

	int i = 0;
	char ch;
	while ( (ch=getchar()) != '\n' ) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

int main ( int argc , char * argv[] ) {

	int t , count = 0;
	scanf("%d" , &t);

	int array[1000][1000];

	while ( t != 0 ) {

		count ++;
		int total_flow = 0;
		int net_flow = 0;

		int i , j;
		for ( i = 0 ; i < t ; i++ ) {
			for ( j = 0 ; j < t ; j++ ) {
				scanf("%d" , &array[i][j] );
				total_flow += (array[i][j]);
			}
		}

		for ( i = 0 ; i < t ; i++ ) {
			int out_flow = 0;
			int in_flow = 0;

			for ( j = 0 ; j < t ; j++ ) {
				out_flow += (array[i][j]);
				in_flow += (array[j][i]);
			}

			if ( out_flow >= in_flow ) {
				net_flow += (out_flow - in_flow);
			}
		}

		printf("%d. %d %d\n" , count , total_flow , net_flow );

		scanf("%d" , &t);

	}

	return 0;
}
