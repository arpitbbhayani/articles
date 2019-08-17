```c
class Solution {
public:
    int removeDuplicates(int A[], int n) {

        if( n == 0 ) {
            return 0;
        }

        int index = 1;
        int curr = A[0];
        for( int i = 1 ; i < n ; i++ ) {
            if( A[i] == curr ) {
                
            }
            else {
                A[index++] = A[i];
                curr = A[i];
            }
        }
        return index;
    }
};
```
