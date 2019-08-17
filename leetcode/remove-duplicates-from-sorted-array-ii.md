```
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        
        if( n == 0 ) {
            return 0;
        }
        
        int count = 1;
        int last = A[0];
        int index = 1;
        
        for( int i = 1 ; i < n ; i++ ) {
            
            if( A[i] == last && count == 1 ) {
                A[index++] = A[i];
                count++;
            }
            else if( A[i] == last ) {
                
            }
            else {
                A[index++] = A[i];
                count = 1;
                last = A[i];
            }
            
        }
        return index;
    }
};
```
