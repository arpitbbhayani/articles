class Solution {
public:
    int maxArea(vector<int> &height) {
        
        int result = INT_MIN;
        
        int low = 0 , high = height.size()-1;
        
        while ( low < high ) {
            
            int area = (high-low) * min(height[high] , height[low]);
            
            if( height[low] < height[high] ) {
                low++;
            }
            else {
                high--;
            }
            
            result = max(result,area);
            
        }
        
        return result;
    }
};
