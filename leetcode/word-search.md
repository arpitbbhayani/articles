```
class Solution {
public:
    
    int ** visited;
    
    const char * str;
    
    int row = 0 , col = 0;
    
    int nx[4] = {-1,1,0,0};
    int ny[4] = {0,0,-1,1};
    
    bool issafe( int x, int y ) {
        if( x >=  0 && x < row && y >= 0 && y < col ) {
            return true;
        }
        return false;
    }
    
    bool check( vector< vector<char> > &board, int i, int j, const char * str ) {
        
        if( visited[i][j] == 1 ) {
            return false;
        }
        
        if( board[i][j] == *str && *(str+1) == '\0' ) {
            return true;
        }
        
        visited[i][j] = 1;
        
        if( board[i][j] == *str ) {
            for( int k = 0 ; k < 4 ; k++ ) {
                int newx = i + nx[k];
                int newy = j + ny[k];
                
                if( issafe(newx,newy) ) {
                    bool temp = check(board,newx,newy,str+1);
                    if( temp == true ) {
                        return true;
                    }
                }
            }
        }
        
        visited[i][j] = 0;
        
        return false;
        
    }
    
    bool exist(vector<vector<char> > &board, string word) {
        
        str = word.c_str();
        row = board.size();
        col = board[0].size();
        
        
        visited = (int **) calloc(sizeof(int *) , row);
        for( int i = 0 ; i < row ; i++ ) {
            visited[i] = (int *) calloc(sizeof(int) , col);
        }
        
        for( int i = 0 ; i  < row ; i++ ) {
            for( int j = 0 ; j < col ; j++ ) {
                if( board[i][j] == str[0] ) {
                    bool ans = check(board,i,j,str);
                    if( ans == true ) {
                        return true;
                    }
                }
            }
        }
        
        return false;
        
    }
};
```
