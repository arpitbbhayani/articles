```
#include<iostream>
#include<algorithm>
#include<cstdio>

using namespace std;

typedef long long LL;

int a[1000001];

LL compute(LL x)
{
  if(x<=11)
      return x;
  else
       {
           if(x<=1000000)
             {
                if(a[x]==0)
                   {
                      a[x]=max(x,(compute(x/2)+compute(x/3)+compute(x/4)));
                      return a[x];
                   }
               else 
                   return a[x];
             }
           else 
                 return(max(x,(compute(x/2)+compute(x/3)+compute(x/4))));
       }
}
int main()
{
     LL x;
     while(scanf("%lld",&x)!=-1)
      {
        cout<<compute(x)<<endl;   
      }  
 return 0;
}
```
