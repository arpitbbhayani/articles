```c
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        
        if( prices.size() == 0)
            return 0;
        
        int minv = prices[0];
        int maxv = 0;
        
        for( int i = 1 ; i < prices.size() ; i++ ) {
            
            maxv = max(maxv,prices[i] - minv);
            minv = min(minv,prices[i]);
        }
        
        return maxv;
        
    }
};
```
