#include<stdio.h>
#include<string.h>

int main( int argc , char * argv[] ) {
	int t;
	scanf("%d",&t);

	while(t) {
		char arr[300];
		scanf( "%s" , arr );
		int len = strlen(arr) / t;

		char ans[len][t];

		int i , j , k = 0;

		for( i = 0 ; i < len ; i++ ) {
			if( i % 2 ) {
				for( j = t - 1 ; j >= 0 ; j-- ) {
					ans[i][j] = arr[k++];
				}
			}
			else {
				for( j = 0 ; j < t ; j++ ) {
					ans[i][j] = arr[k++];
				}
			}
		}

		for( i = 0 ; i < t ; i++ ) {
			for( j = 0 ; j < len ; j++ ) {
				printf("%c",ans[j][i]);
			}
		}

		printf("\n");

		scanf("%d",&t);
	}

	return 0;

}
