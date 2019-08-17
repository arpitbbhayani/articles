```
class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        
        int n = matrix.size();
        
        for( int i = 0 ; i < n-1 ; i++ ) {
            for( int j = i+1;  j < n ; j++ ) {
                int t = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = t;
            }
        }
        
        int start = 0 , end = n-1;
        
        for( int j = 0 ; j < n/2 ; j++  ) {
            
            for( int i = 0 ; i < n ; i++ ) {
                int t = matrix[i][start];
                matrix[i][start] = matrix[i][end];
                matrix[i][end] = t;
            }
            start++;
            end--;
        }
    }
};
```
