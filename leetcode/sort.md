class Solution {
public:
    void sortColors(int A[], int n) {
        int c[3] = {0};
        
        for( int i = 0 ; i < n ; i++ ) {
            c[A[i]]++;
        }
        
        int k = 0;
        int index = 0;
        while ( index < 3 ) {
            for( int i = 0 ; i < c[index] ; i++ ) {
                A[k++] = index;
            }
            index++;
        }
    }
};
