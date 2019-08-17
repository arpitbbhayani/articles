```c
class Solution {
public:

    int f( int * A , int n ) {
        
        for( int i = 0 ; i < n ; i++ ) {
            int index = abs(A[i]) - 1;
            if( index < n && A[index] > 0 ) {
                A[index] *= -1;
            }
        }
        
        int i = 0;
        for( ; i < n ; i++ ) {
            if( A[i] > 0 ) {
                break;
            }
        }
        
        return i + 1;
    }

    int firstMissingPositive(int A[], int n) {
        
        int index = 0;
        for( int i = 0 ; i < n ; i++ ) {
            if( A[i] <= 0 ) {
                int t = A[i];
                A[i] = A[index];
                A[index] = t;
                index++;
            }
        }
        //cout << "Index = " << index << " and a[index] = " << A[index] << endl;
        return f(&A[index], n - index);
        
    }
};
```
