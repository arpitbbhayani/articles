#include <iostream>
#include <cstdio>
 
using namespace std;

int rev(int n) {
	int r=0;
	while( n ) {
		r=r*10+(n%10);
		n/=10;
	}
	return r;
}

int main() {

	int t,n1,n2;
	scanf("%d",&t);

	while(t--) {

		scanf("%d%d",&n1,&n2);
		printf("%d\n",rev(rev(n1)+rev(n2)));
	}

	return 0;
}
