```c
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

int readline ( char * str ) {

	int i = 0;
	char ch;
	while ( (ch=getchar()) != '\n' ) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

struct node {
	int a;
	int b;
};

struct node array[10010];
int lis[10010];

int compar ( const void * a , const void * b ) {
	struct node * x = (struct node *) a;
	struct node * y = (struct node *) b;

	if ( x->a == y->a ) {
		return x->b - y->b;
	}
	return x->a - y->a;


}

int main ( int argc , char * argv[] ) {

	int t , z , i , j;
	scanf("%d" , &t);
	for ( z = 1 ; z <= t ; z++ ) {

		int n;
		scanf("%d" , &n);
		for ( i = 0 ; i < n ; i++ ) {
			scanf("%d" , &array[i].a);
		}
		for ( i = 0 ; i < n ; i++ ) {
			scanf("%d" , &array[i].b);
		}

		qsort( array , n , sizeof(struct node) , compar);

		#if DEBUG
			for ( i = 0 ; i < n ; i++ ) {
				printf("%d " , array[i].a);
			}
			printf("\n");
			for ( i = 0 ; i < n ; i++ ) {
				printf("%d " , array[i].b);
			}
			printf("\n");
		#endif

		for ( i = 0 ; i < n ; i++ ) {
			lis[i] = 1;
		}

		for ( i = 1 ; i < n ; i++ ) {
			for ( j = 0 ; j < i ; j++ ) {
				if ( array[i].b >= array[j].b && lis[i] < lis[j]+1 )
					lis[i] = lis[j] + 1;
			}
		}

		#if DEBUG
			printf("LIS Table\n");
			for ( i = 0 ; i < n ; i++ ) {
				printf("%d " , lis[i]);
			}
			printf("\n");
		#endif

		int max = lis[0];
		for ( i = 1 ; i < n ; i++ ) {
			if ( lis[i] > max )
				max = lis[i];
		}

		printf("%d\n" , max);

	}
	return 0;
}
```
