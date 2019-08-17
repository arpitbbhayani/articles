#include <stdlib.h>
#include <stdio.h>

void merge(int a[],int l, int m, int h);
int partition(int a[], int l, int h); 
void mergesort(int a[], int l, int h); 

void mergesort(int a[], int l, int h) 
{
	int m;
	if (l >= h) return;
	m = partition(a, l, h);
	mergesort(a, l, m);
	mergesort(a, m+1, h);
	merge(a, l, m, h);
}
int partition(int a[], int l, int h) 
{
	return (l+h)/2;
}
void merge(int a[],int l, int m, int h) 
{
	int b[10000];
	int i, j, k;
	k = l;
	i = l;
	j = m + 1;
	while (i <= m  && j <= h) 
	{
		if (a[i] < a[j]) 
			b[k++] = a[i++];
		else 
			b[k++]= a[j++];
	}
	if (i > m ) 
		while(j <= h) 
			b[k++] = a[j++];
	else if (j > h) 
		while (i <= m) 
			b[k++] = a[i++];
	k = l;
	while(k <= h) 
	{ 
		a[k] = b[k]; 
		k++;
	}
}


int comp(const void * a,const void * b)
{
    if (*(int*)a==*(int*)b)
        return 0;
    else if (*(int*)a < *(int*)b)
        return -1;
    else
        return 1;
}

int main()
{
	int x , y , n;
	int a[10000] , i , j;
	int b[10000];

	scanf("%d" , &n);

	while( n-- ) {
	scanf("%d" , &x);
	for (i = 0; i < x; i++) {
	        scanf ("%d", &a[i]);
	}
	scanf("%d" , &y);
	for (i = 0; i < y; i++) {
	        scanf ("%d", &b[i]);
	}

	mergesort(a,0,x-1) ;
	mergesort(b,0,y-1) ;

	i = 0; j = 0;

	int * inc;
	int minimum = abs(a[0]-b[0]);
	while (minimum > 0 && (i < (x - 1) || j < (y - 1))) {

        int z;
        if ( i == x-1)
        {
            inc = &j;
            z = abs(a[i]-b[j+1]);
        }
        else if ( j == y -1 )
        {
            inc = &i;
            z = abs(a[i+1]-b[j]);
        }
        else
        {
            int zi = abs(a[i+1]-b[j]);
            int zj = abs(a[i]-b[j+1]);
            if ( zi < zj)
            {
                inc = &i;
                z = zi;
            }
            else
            {
                inc = &j;
                z = zj;
            }
        }
        if ( z < minimum)
        {
            minimum = z;
        }

        (*inc)++;
    }
    printf ("%d\n", minimum);
	}
    return 0;

}
