```
class Solution {
public:
    int findMin(vector<int> &num) {
        
        int m = num[0];
        for( int i = 1; i < num.size() ; i++ ) {
            m = min(m,num[i]);
        }
        return m;
        
    }
};
```
