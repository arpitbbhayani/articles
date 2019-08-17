```c
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        
        int n = s.length();
        int hash[256];
        
        for( int i = 0 ; i < 256; i++ ) {
            hash[i] = -1;
        }
        
        int i = 0;
        for( ; i < n ; i++ ) {
            if( hash[s[i]] == -1 ) {
                hash[s[i]] = i;
            }
            else {
                break;
            }
        }
        
        int start = 0 , end = i-1;
        int result = end-start + 1;
        
        for( i = i; i < n ; i++ ) {
            
            char c = s[i];
            int lastindex = hash[c];
            
            if( lastindex == -1 ) {
            }
            else if( lastindex != -1 && lastindex >= start ) {
                start = lastindex + 1;
            }
            
            end = i;
            hash[c] = i;
            result = max(result,end-start+1);
        }
        
        result = max(result,end-start+1);
        return result;
        
    }
};
```
