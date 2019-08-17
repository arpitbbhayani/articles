```c
/*
 * ARMY.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>

using namespace std;

#define DEBUG 0

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);
	while (t--) {
		int n, m, x;
		int ma = INT_MIN, mb = INT_MIN;
		scanf("%d%d", &n, &m);

		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			if (x > ma)
				ma = x;
		}

		for (int i = 0; i < m; i++) {
			scanf("%d", &x);
			if (x > mb)
				mb = x;
		}

		if ( ma >= mb ) {
			printf("Godzilla\n");
		}
		else {
			printf("MechaGodzilla\n");
		}

	}
	return 0;
}
```
