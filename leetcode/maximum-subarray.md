```c
class Solution {
public:
    int maxSubArray(int A[], int n) {
        
        int flagn = 0 , flagp = 0;
        
        for( int i = 0 ; i < n ;i++ ) {
            if( A[i] < 0 ) {
                flagn = 1;
            }
            else {
                flagp = 1;
            }
            
            if( flagn == 1 && flagp == 1 )
            break;
            
        }
        
        int result = A[0];
        if( flagn == 1 && flagp == 0 ) {
            for( int i = 1; i < n ; i++ ) {
                result = max(result,A[i]);
            }
            return result;
        }
        
        result = 0;
        if( flagn == 0 && flagp == 1 ) {
            for( int i = 0 ; i < n ; i++ ) {
                result += A[i];
            }
            return result;
        }
        
        int temp = 0;
        for( int i = 0 ; i < n ;  i++ ) {
            temp += A[i];
            if( temp < 0 ) {
                temp = 0;
            }
            result = max(result,temp);
        }
        return result;
    }
};
```
