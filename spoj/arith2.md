```
#include<cstdio>
#include<cstring>
#include<cstdlib>
 
using namespace std ;
 
int main( )
{
        int i , j , n , t , ctr = 0 ;
        long long ans , a , b ;
        char op , str[1000000] , buffer[2500] , buffer2[2500] ;
    
        scanf("%d",&t) ;
        t += 1 ;
        
        while( t-- )
        {
                ctr++ ;
                gets( str ) ;
                n = strlen( str ) ;
                if( n == 0 )
                {
                    gets( str ) ;
                    n = strlen( str ) ;
                }
                
                for( i = 0 ; i < n ; )
                {
                        memset( buffer , 0 , sizeof( buffer ) ) ;
                        j = 0 ;
                        while( str[i] == ' ' )
                                i++ ;
                        while( str[i] != ' ' )
                                buffer[j++] = str[i++] ;
                        buffer[j] = '\0' ;
                        a = atoi( buffer ) ;
                        ans = a ;
                        while( str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' )
                                i++ ;
                        op = str[i] ;
                        i++ ;
                        while( str[i] == ' ' )
                                i++ ;
                        break ;
                }
                 
                for( ; i < n ; )
                {
                        j = 0 ;
                        memset( buffer2 , 0 , sizeof( buffer2 ) ) ;
                        while( str[i] != ' ' && str[i] != '=' )
                                buffer2[j++] = str[i++] ;
                        buffer2[j] = '\0' ;
                        b = atoi( buffer2 ) ;
                        if( op == '+' )
                                ans += b ;
                        else if( op == '-' )
                                ans -= b ;
                        else if( op == '*' ) 
                                ans *= b ;
                        else if( op == '/' )
                                ans /= b ; 
                        while( str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' )
                                i++ ;
                        op = str[i] ;
                        i++ ;
                        while( str[i] == ' ' )
                                i++ ;
                }
                
                if( ctr != 1 )
                        printf("%lld\n",ans) ;
        }
        
        return 0 ; 
}
```
