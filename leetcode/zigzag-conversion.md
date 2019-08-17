```
class Solution {
public:
    string convert(string s, int nRows) {
        vector< char > t[nRows];
        
        int index = 0;
        int direction = 1;
        
        for( int i = 0 ; i < s.length(); i++ ) {
            t[index].push_back(s[i]);
            index += direction;
            
            if( direction == 1 ) {
                index = min(index, nRows-1);
            }
            else {
                index = max(index,0);
            }
            
            if( index == nRows-1 || index == 0) {
                direction *= -1;
            }
            
        }
        
        string result;
        for( int i = 0 ; i < nRows ; i++ ) {
            for( int j = 0 ; j < t[i].size(); j++ ) {
                result.append<char>(1,t[i][j]);
            }
        }
        
        return result;
        
    }
};
```
