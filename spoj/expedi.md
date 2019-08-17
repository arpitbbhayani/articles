#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

struct node {
	long int dist;
	long int fuel;
};

int compar1 ( const void * a , const void * b ) {
	long int * x = (long int *) a;
	long int * y = (long int *) b;
	return (*x) - (*y);
}

int compar ( const void * a , const void * b ) {
	struct node * x = (struct node *) a;
	struct node * y = (struct node *) b;
	return (*y).dist - (*x).dist;
}

int main ( int argc , char * argv[] ) {

	int t;
	scanf("%d" , &t);

	while ( t-- ) {

		int n , i;
		scanf("%d" , &n);
		n+=1;

		struct node *list = (struct node*) malloc ( n * (sizeof(struct node) ));
		int *list_fuel = (int*) malloc ( n * (sizeof(int) ));
		int index = -1;

		for ( i = 0 ; i < n ; i++ ) {
			scanf("%ld%ld" , &list[i].dist , &list[i].fuel);
		}
		qsort(list , n , sizeof(struct node) , compar);
		
		#if DEBUG
		printf("Distance and fuel:\n");
		for ( i = 0 ; i < n ; i++ ) {
			printf("%ld %ld\n" , list[i].dist , list[i].fuel);
		}
		#endif


		long int cur_dist = list[0].dist;
		long int cur_fuel = 0;
		int count = 0;

		for ( i = 0 ; i <= n ; i++ ) {
			cur_fuel -= (cur_dist - list[i].dist);
			cur_dist = list[i].dist;

			while ( cur_fuel < 0 ) {

				if ( index == -1 ) {
					count = -1;
					break;
				}

#if DEBUG
				printf("Purchase fuel amount -> %ld\n" , list_fuel[index]);
#endif

				cur_fuel += list_fuel[index--];
				count ++;
			}

			if ( count == -1 ) {
				break;
			}

#if DEBUG
			printf("Adding to list_fuel : %ld\n" , list[i].fuel);
#endif
			list_fuel[++index] = list[i].fuel;
			qsort(list_fuel , index+1 , sizeof(int) , compar1 );

		}
		if ( count > -1 )
			count --;
		printf("%d\n" , count);
	}

	return 0;
}
