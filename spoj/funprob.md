```
#include <stdio.h>

int main( int argc , char * argv[] ) {

	int n,m;

	scanf("%d%d",&n,&m);

	while( n != 0 || m != 0 ) {

		if(n>m)
			printf("0.000000\n");
		else
			printf("%0.6lf\n",(double)(m-n+1)/(double)(m+1));
	
		scanf("%d%d",&n,&m);
	}

	return 0;
}
```
