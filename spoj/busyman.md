```c
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
struct node {
	int a;
	int b;
};

int compar(const void *a, const void *b) {
	struct node *x = (struct node *)a;
	struct node *y = (struct node *)b;

	return x->b - y->b;

}

int main ( int argc , char * argv[] ) {

	int t;
	scanf("%d" , &t);

	while ( t-- ) {
		int n , i;
		scanf("%d" , &n);

		struct node * array = (struct node *) calloc ( n , sizeof(struct node) );

		for ( i = 0 ; i < n ;i++ ) {
			scanf("%d%d" , &array[i].a , &array[i].b);
		}

		qsort ( array , n , sizeof(struct node) , compar );

		int pb = array[0].b;
		int count = 1;

		for ( i = 1 ; i < n ;i++ ) {
			if ( array[i].a >= pb ) {
				pb = array[i].b;
				count ++;
			}
		}

		printf("%d\n" , count);
		
		free(array);
	}

	return 0;
}
```
