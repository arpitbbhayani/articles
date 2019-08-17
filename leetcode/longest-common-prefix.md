```
class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        string result;
        
        if( strs.size() == 0 ) {
            return result;
        }
        
        int len = INT_MAX;
        for( int i = 0 ; i < strs.size(); i++ ) {
            len = min(len,(int)strs[i].length());
        }
        
        for( int col = 0; col < len; col++ ) {
            
            int do_all_match = 1;
            for( int i = 0 ; i < strs.size() - 1 ; i++ ) {

                if( strs[i][col] == strs[i+1][col] ) {
                    
                }
                else {
                    do_all_match = 0;
                    break;
                }
            }
            
            if( do_all_match == 1 ) {
                result.push_back(strs[0][col]);
            }
            else {
                break;
            }
            
        }
        
        return result;
    }
};
```
