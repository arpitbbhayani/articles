```
#include <stdio.h>

int eval(int , int * );

int main( int argc , char * argv[] ) {

	int i , j , num , ele[10000] , output[10000] , totalCase = 0;

	do {
		scanf("%d" , &num);
		if(num == -1)
			break;

		totalCase ++;

		for( j = 0 ; j < num ; j++ ) {
			scanf( "%d" , &ele[j] );
		}

		output[totalCase - 1] = eval(num , ele);


	} while (1);

	for( i = 0 ; i < totalCase ; i++ ) {
		printf("%d\n",output[i]);
	}
	return 0;
}

int eval(int num , int * ele) {

	int i , sum = 0 , average = 0;
	float avg = 0.0;
	int count = 0 , check = 0;
	for(i = 0 ; i < num ; i++) {
		sum += ele[i];
	}
	avg = (float) (sum / (float) num);

	average ++;

	if(avg - (int) avg == 0) {
		average = (int) avg;
		for(i = 0 ; i < num ; i++ ) {
			int diff = ele[i] - average;
			//printf(" Checking for element = %d , average = %d\n" , ele[i] , average);
			if(diff > 0) {
				check = check + diff;
				count += diff;
				//printf("Removing from element %d and check = %d\n" , diff , check);
			}
			else if( diff < 0) {

				check = check + diff;
				//count += (-1 * diff);
				//printf("moving into element %d and check = %d\n" , diff , check);
			}
		}
		if(check == 0)
			return count;
		else
			return -1; 
	}
	else {
		return -1;
	}


	return 0;
}
```
