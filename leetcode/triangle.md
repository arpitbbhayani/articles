```
class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        
        int n = triangle.size();
        
        if( n == 1) {
            return triangle[0][0];
        }
        
        for( int i = n-2 ; i >= 0 ; i-- ) {
            for( int j = 0; j < triangle[i].size() ; j++ ) {
                triangle[i][j] = min(triangle[i][j] + triangle[i+1][j], triangle[i][j] + triangle[i+1][j+1]);
            }
        }
        
        return triangle[0][0];
    }
};
```
