```c
/*
 * ARBITRAG.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>

using namespace std;

#define DEBUG 0

map<string, int> nodes;
double d[300][300];

int main(int argc, char * argv[]) {

	int n, m;
	string a, b, c;
	int i, j;
	double k1;
	int z = 1;

	while (1) {

		nodes.clear();
		cin >> n;

		if (n == 0)
			break;

		for (i = 0; i < n; i++) {
			cin >> a;
			nodes[a] = i;
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				d[i][j] = 0.0;
			}
		}

		cin >> m;

		for (int l = 0; l < m; l++) {
			cin >> a >> k1 >> b;
			i = nodes.find(a)->second;
			j = nodes.find(b)->second;
			d[i][j] = k1;
		}

		for (int k = 0; k < n; k++) {
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					if (d[i][k] * d[k][j] > d[i][j])
						d[i][j] = d[i][k] * d[k][j];
				}
			}
		}

		for (i = 0; i < n; i++) {
			if (d[i][i] > 1.0)
				break;
		}

		cout << "Case " << z << ": ";
		if (i == n) {
			cout << "No" << endl;
		} else {
			cout << "Yes" << endl;
		}
		z++;

	}

	return 0;
}
```
