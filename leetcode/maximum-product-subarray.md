```c
class Solution {
public:

    int max3(int a, int b, int c) {
        return max(a,max(b,c));
    }
    
    int min3(int a, int b, int c) {
        return min(a,min(b,c));
    }

    int result;
    int maxp = INT_MIN, minn = INT_MAX;
    int oldmaxp, oldminn;

    int maxProduct(int A[], int n) {
        
        if(n == 0) {
            return 0;
        }
        
        result = A[0];
        oldmaxp = max(A[0],1);
        oldminn = min(A[0],1);
        
        for( int i = 1 ; i < n ; i++ ) {
            maxp = max3(oldmaxp * A[i], oldminn * A[i], A[i]);
            minn = min3(oldminn * A[i], oldmaxp * A[i], A[i]);
            result = max(result, maxp);
            oldmaxp = maxp;
            oldminn = minn;
        }
        return result;
        
    }
};
```
