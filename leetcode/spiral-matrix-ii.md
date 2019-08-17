```c
class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
        vector<int> row(n,0);
        vector< vector<int> > matrix;
        
        for( int i = 0 ; i < n ; i++ ) {
            matrix.push_back(row);
        }
        
        
        int left = 0, right = n, top = 0, bottom = n;
        int index = 1;
        
        while ( top < bottom && left < right ) {
            
            if( top < bottom ) {
                for( int i = left ; i < right ; i++ ) {
                    matrix[top][i] = index++;
                }
                top++;
            }
            
            if( left < right ) {
                for( int i = top; i < bottom ; i++ ) {
                    matrix[i][right-1] = index++;
                }
                right--;
            }
            
            if( top < bottom ) {
                for( int i = right-1; i >= left ; i-- ) {
                    matrix[bottom-1][i] = index++;
                }
                bottom--;
            }
            
            if( left < right ) {
                for( int i = bottom-1; i >= top ; i--) {
                    matrix[i][left] = index++;
                }
                left++;
            }
            
        }
        
        return matrix;
        
        
    }
};
```
