class Solution {
public:
    int maxProfit(vector<int> &prices) {

        int n = prices.size();

        if( n == 0 ) {
            return 0;            
        }

        int profit = 0;
        int buy = prices[0];
        int sell = INT_MIN;
        
        for( int i = 1 ; i < n ; i++ ) {
            
            if( prices[i] < prices[i-1] ) {
                sell = prices[i-1];
                profit += (sell-buy);
                buy = prices[i];
            }
            
        }
        sell = prices[n-1];
        profit += (sell-buy);
        return profit;
    }
};
