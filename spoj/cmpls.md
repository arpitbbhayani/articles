```c
/*
 * CMPLS.cpp
 *
 *  Created on: Apr 30, 2014
 *      Author: Arpit Bhayani
 *
 *
 *  http://www.algorithmist.com/index.php/SPOJ_CMPLS
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define DEBUG 0
#define gc getchar
#define ll long long

int main(int argc, char * argv[]) {

	int t;
	scanf("%d", &t);

	while (t--) {

		vector<int> last_val;
		vector<int> diff;

		int d = -1;	// difference

		int n, k;
		int flag = 0;

		scanf("%d%d", &n, &k);

		int temp, temp_old;

		for (int i = 0; i < n; i++) {

			scanf("%d", &temp);

			if (i != 0) {
				d = temp - temp_old;

				if (flag == 0)
					flag = d;

				diff.push_back(d);

			}

			if (i == n - 1) {
				last_val.push_back(temp);
				last_val.push_back(d);
			}

			temp_old = temp;

		}

		if (n == 1) {
			for (int i = 0; i < k; i++) {
				//if (i != 0)
				//	printf(" ");
				printf("%d ", last_val[0]);
			}
			continue;
		}

		d = -1;

		while (flag != 0) {

			int temp_flag = 0;

			for (int i = 0; i < diff.size() - 1; i++) {

				d = diff[i + 1] - diff[i];

				if (temp_flag == 0)
					temp_flag = d;

				diff[i] = d;

				if (i == diff.size() - 2)
					last_val.push_back(d);

			}

			diff.pop_back();

			if (temp_flag == 0)
				flag = 0;

			if (diff.size() == 1)
				flag = 0;

		}

		if (last_val[last_val.size() - 1] == 0)
			last_val.pop_back();

#if DEBUG
		cout << "DIFF Vector : ";
		for (vector<int>::iterator itr = diff.begin(); itr != diff.end();
				itr++) {
			cout << *itr << " ";
		}
		cout << endl;
		cout << "LAST VAL Vector : ";
		for (vector<int>::iterator itr = last_val.begin();
				itr != last_val.end(); itr++) {
			cout << *itr << " ";
		}
		cout << endl;
#endif

		for (int i = 0; i < k; i++) {
			for (int j = last_val.size() - 2; j >= 0; j--) {
				last_val[j] = last_val[j] + last_val[j + 1];
			}
			//if (i != 0)
			//	printf(" ");
			printf("%d ", last_val[0]);
		}
		printf("\n");

	}
	return 0;
}
```
