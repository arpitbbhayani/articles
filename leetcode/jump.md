class Solution {
public:
    bool canJump(int A[], int n) {
        
        int count = 0;
        
        for( int i = 0 ; i < n-1 ; ) {
            
            int m = INT_MIN;
            int mi = i;
            int jumpsize = A[i];
            for( int j = 0 ; j < jumpsize; j++ ) {
                if( i + j + 1 < n-1 && i + j + 1 + A[i+j+1] > m ) {
                    m = i + j + 1 + A[i+j+1];
                    mi = i + j + 1;
                }
                
                if( i + j + 1 >= n-1 ) {
                    return true;
                }
            }
            
            if( m == INT_MIN ) {
                return false;
            }
            else {
                i = mi;
            }
            
        }
        
        return true;
        
    }
};
