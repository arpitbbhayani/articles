```c
#include <stdio.h>
#include <stdlib.h>

#define MAXN 35

unsigned long long int answer;

int N, A, B;

int seq[MAXN];

int numbers[2][1<<20];
int count[2];

int intCmp(const void *ap, const void *bp){
	int a = *(int *)ap;
	int b = *(int *)bp;
	if (a > b) return 1;
	else if (a < b) return -1;
	else return 0;
}

int generateSubsets(int arr[1<<20], int *seq, int c){
	int i, j;
	for (i = 0; i < (1<<c); i++)
		for (j = 0; j < c; j++)
			if (i & (1<<j))
				arr[i] += seq[j];
	return 1<<c;
}

int lower(int n){
	int lo = 0, hi = count[1], mid;

	while (lo < hi){
		mid = (lo + hi) / 2;
		if (n + numbers[1][mid] >= A)
			hi = mid;
		else
			lo = mid + 1;
	}

	return hi;
}

int upper(int n){
	int lo = 0, hi = count[1], mid;

	while (lo < hi){
		mid = (lo + hi) / 2;
		if (n + numbers[1][mid] <= B)
			lo = mid + 1;
		else
			hi = mid;
	}

	return lo - 1;
}

int main(void){
	int i;

	scanf("%d %d %d", &N, &A, &B);

	for (i = 0; i < N; i++)
		scanf("%d", &seq[i]);

	count[0] = generateSubsets(numbers[0], seq, (N+1)/2);
	count[1] = generateSubsets(numbers[1], seq + (N+1)/2, N/2);

	qsort(numbers[0], count[0], sizeof(numbers[0][0]), intCmp);
	qsort(numbers[1], count[1], sizeof(numbers[1][0]), intCmp);

	int lo = count[1] - 1, hi = count[1] - 1;

	for (i = 0; i < count[0]; i++){
		int lo = lower(numbers[0][i]);
		int hi = upper(numbers[0][i]);
		if (lo <= hi)
			answer += hi - lo + 1;
	}

	printf("%llu\n", answer);

	return 0;
}
```
