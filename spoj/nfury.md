#include<stdio.h>
int main()
{
	int a[32]={1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256,289,324,361,400,441,484,529,576,625,676,729,784,841,900,961};
	int i,t,j;
	int dp[1005];
	dp[1]=1;
	dp[2]=2;
	dp[3]=3;
	for(i=4;i<=1000;i++)
	{
		dp[i]=i;
		for(j=0;j<31;j++)
		{
			if(a[j]<=i && dp[i]>dp[i-a[j]]+1)
				dp[i]=dp[i-a[j]]+1;
		}
	}
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		printf("%d\n",dp[n]);
	}
	return 0;
}
