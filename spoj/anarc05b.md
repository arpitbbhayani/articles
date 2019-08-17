/*
 * ANARC05B.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: Arpit Bhayani
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define DEBUG 0

int a[11000], b[11000];

int max(int c, int d) {
	return c > d ? c : d;
}

int main(int argc, char * argv[]) {

	int n, m;
	scanf("%d" , &n);

	while (n != 0) {

		for (int i = 0; i < n; i++)
			scanf("%d" , &a[i]);

		scanf("%d" , &m);
		for (int i = 0; i < m; i++)
			scanf("%d" , &b[i]);

		int suma = 0, sumb = 0, result = 0;
		int i = 0, j = 0;

		while (1) {

			if (i < n && j < m && a[i] < b[j]) {
				suma += a[i];
				//cout << "suma = " << suma << endl;
				i++;
			} else if (i < n && j < m && b[j] < a[i]) {
				sumb += b[j];
				//cout << "sumb = " << sumb << endl;
				j++;
			} else if (i < n && j < m && a[i] == b[j]) {
				result += max(suma + a[i], sumb + b[j]);
				//cout << "result = " << result << endl;
				suma = sumb = 0;
				i++;
				j++;
			}

			if ( i >= n && j >= m )
				break;

			if ( i >= n ) {
				//cout << "adding remaining b" << endl;
				while ( j < m ) {
					sumb += b[j];
					j++;
				}
				result += max(suma , sumb);
				break;
			}

			if ( j >= m ) {
				//cout << "adding remaining a" << endl;
				while ( i < n ) {
					suma += a[i];
					//cout << "suma = " << suma << endl;
					i++;
				}
				//cout << " max of : " << suma << " and " << sumb << endl;
				result += max(suma, sumb);
				//cout << "result = " << result << endl;
				break;
			}

		}

		cout << result << endl;

		scanf("%d" , &n);
	}

	return 0;
}
