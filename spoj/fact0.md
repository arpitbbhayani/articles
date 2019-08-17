/*
 * FACT0.c
 *
 *  Created on: Sep 3, 2014
 *      Author: Arpit Bhayani
 */

#include <stdio.h>
#include <stdlib.h>

#define si(x) scanf("%d" , &x)
#define sl(x) scanf("%ld" , &x)
#define sll(x) scanf("%lld" , &x)
#define sc(x) scanf("%c" , &x)
#define ss(x) scanf("%s" , &x)

#define pi(x) printf("%d\n" , x)
#define pl(x) printf("%ld\n" , x)
#define pll(x) printf("%lld\n" , x)
#define pc(x) printf("%c\n" , x)
#define ps(x) printf("%s\n" , x)

#define fup(i,a,b) for(int i=a;i<b;i++)
#define fdn(i,a,b) for(int i=a;i>=b;i--)

#define DEBUG 0
#define gc getchar
#define ll unsigned long long

int main(int argc, char * argv[]) {

	ll int n;
	scanf("%llu", &n);

	while (n != 0LL) {

		if (n == 1LL) {
			printf("1^1 \n");
			scanf("%llu", &n);
			continue;
		}

		int count = 0;

		while ((n & 1) == 0) {
			count++;
			n /= 2LL;
		}

		if (count != 0) {
			printf("2^%d ", count);
		}

		ll int i = 3LL;

		for (; i * i <= n; i += 2LL) {

			if (n % i == 0) {

				count = 0;
				while (n % i == 0) {
					count++;
					n /= i;
				}

				printf("%llu^%d ", i, count);
			}

			if (n == 1LL)
				break;
		}

		if (n > 1) {
			printf("%llu^1 ", n);
		}

		printf("\n");
		scanf("%llu", &n);
	}
	return 0;
}
