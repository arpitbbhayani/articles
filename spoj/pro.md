```c
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>

#define DEBUG 1

using namespace std;

int main ( int argc , char * argv[] ) {

	multiset<int> set;
	multiset<int> :: iterator f,r;

	int n;
	long long int cost = 0;

	scanf("%d" , &n);

	while ( n-- ) {
		int k;
		scanf("%d" , &k);
		int i = 0;
		for ( i = 0 ; i < k ; i++ ) {
			int x;
			scanf("%d" , &x);
			set.insert(x);
		}
		f = set.begin();
		r = set.end();
		r --;
		cost += (*r - *f);
		set.erase(f);
		set.erase(r);
	}

	cout << cost << endl;

	return 0;
}
```
