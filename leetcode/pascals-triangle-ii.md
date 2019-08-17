```c
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        
        vector<int> ans;
        ans.push_back(1);
        
        for( int i = 0 ; i < rowIndex ; i++ ) {
            ans.insert(ans.begin(),1);
            for( int j = 1 ; j < ans.size() - 1 ; j++ ) {
                ans[j] = ans[j] + ans[j+1];
            }
        }
        
        return ans;
    }
};
```
