```c
class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        int row[matrix.size()], col[matrix[0].size()];
        
        for( int i = 0 ; i < matrix.size() ; i++ ) {
            row[i] = 1;
        }
        
        for( int i = 0 ; i < matrix[0].size() ; i++ ) {
            col[i] = 1;
        }
        
        for( int i = 0 ; i < matrix.size() ; i++ ) {
            for( int j = 0 ; j < matrix[i].size() ; j++ ) {
                if( matrix[i][j] == 0 ) {
                    row[i] = 0;
                    col[j] = 0;
                }
            }
        }
        
        for( int i = 0 ; i < matrix.size() ; i++ ) {
            for( int j = 0 ; j < matrix[i].size() ; j++ ) {
                if( row[i] == 0 || col[j] == 0 ) {
                    matrix[i][j] = 0;
                }
            }
        }
        
    }
};
```
