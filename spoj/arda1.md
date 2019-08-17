```c
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<utility>
#include<vector>

using namespace std ;

vector< pair< int , int > > v ;

int main( )
{
  	int i , j , x , y , X , Y , n1 , n2 , m1 , m2 , check ;
	
	scanf("%d %d",&n1,&n2) ;
	
	char home[n1][n2+1] ;
	
	for( i = 0 ; i < n1 ; i++ )
		scanf("%s",home[i]) ;
	
	scanf("%d %d",&m1,&m2) ;
	
	char map[m1][m2+1] ;
	
	for( i = 0 ; i < m1 ; i++ )
		scanf("%s",map[i]) ;
	
	/* for( i = 0 ; i < n1 ; i++ )
		printf("%s\n",home[i]) ;
	
	printf("\n\n") ;
	for( i = 0 ; i < m1 ; i++ )
		printf("%s\n",map[i]) ; */
		
	for( i = 0 ; i <= m1 - n1 ; i++ )
	{
		for( j = 0 ; j <= m2 - n2 ; j++ )
		{
			if( map[i][j] == home[0][0] )
			{
				for( check = 1 , x = 0 , X = i ; x < n1 ; x++ , X++ )
				{
					for( y = 0 , Y = j ; y < n2 ; y++ , Y++ )
					{
						if( map[X][Y] != home[x][y] )
						{
							check = 0 ;
							break ;
						}
					}
				}
				if( check )
					v.push_back( make_pair( i + 1 , j + 1 ) ) ;
			}
		}
	}
	
	if( v.empty( ) )
		printf("NO MATCH FOUND...\n") ;
	else
	{
		sort( v.begin( ) , v.end( ) ) ;
		check = v.end( ) - v.begin( ) ; 
		for( i = 0 ; i < check ; i++ )
			printf("(%d,%d)\n",v[i].first,v[i].second) ;
	}			
	return 0 ;
}
```
