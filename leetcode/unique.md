class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        
        int r = obstacleGrid.size();
        
        if( r == 0 ) return 0;
        
        int c = obstacleGrid[0].size();
        
        int temp[r][c];
        
        int i = 0;
        for( ; i < c ; i++ ) {
            if( obstacleGrid[0][i] == 1 ) {
                break;
            }
            else {
                temp[0][i] = 1;
            }
        }
        
        while ( i < c ) {
            temp[0][i] = 0;
            i++;
        }
        
        i = 0;
        for( ; i < r ; i++ ) {
            if( obstacleGrid[i][0] == 1 ) {
                break;
            }
            else {
                temp[i][0] = 1;
            }
        }
        
        while ( i < r ) {
            temp[i][0] = 0;
            i++;
        }
        
        for( int i = 1 ; i < r ; i++ ) {
            for( int j  = 1 ; j < c ; j++ ) {
                
                if( obstacleGrid[i][j] == 1 ) {
                    temp[i][j] = 0;
                }
                else {
                    temp[i][j] = temp[i-1][j] + temp[i][j-1];
                }
                
            }
        }
        return temp[r-1][c-1];
    }
};
