```
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <deque>

void printKMax(int * arr, int n, int k)
{
    std::deque<int>  Qi(k);
 
    int i;
    for (i = 0; i < k; ++i)
    {
        while ( (!Qi.empty()) && arr[i] >= arr[Qi.back()])
        	Qi.pop_back();  // Remove from rear
 
        Qi.push_back(i);
    }
 
    for ( ; i < n; ++i)
    {
        printf("%d " , arr[Qi.front()]);
 
        while ( (!Qi.empty()) && Qi.front() <= i - k)
            Qi.pop_front();  // Remove from front of queue
 
        while ( (!Qi.empty()) && arr[i] >= arr[Qi.back()])
            Qi.pop_back();
 
        Qi.push_back(i);
    }
 
    printf("%d " , arr[Qi.front()]);
}

int main ( int argc , char * argv[] ) {

	int n , k;
	int * array;

	scanf("%d" , &n);

	array = ( int * ) malloc ( n * sizeof(int) );

	int i , j;
	for ( i = 0 ; i < n ; i++ ) {
		scanf("%d" , &array[i]);
	}

	scanf("%d" , &k);

	/*int max = array[0];
	int max_i = 0;
	for ( j = 0 ; j < k ; j++ ) {
		if ( array[j] > max ) {
			max = array[j];
			max_i = j;
		}
	}

	printf("%d " , max );

	for ( i = k ; i < n ; i++ ) {
		if ( array[i] > max ) {
			// New element greater than max
			max_i = i;
			max = array[i];
		}
		else if ( max_i == i-1 ) {
			// Recalculate max
			int max = array[i];
			for ( j = 0 ; j < k ; j++ ) {
				if ( array[j+1] > max ) {
					max = array[i+j];
					max_i = i+j;
				}
			}
		}
		else {
			// max will remain same
		}
		printf("%d " , max );
	}
	*/

	printKMax(array, n, k);

	printf("\n");
	return 0;
}
```
