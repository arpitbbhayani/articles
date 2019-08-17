```c
class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        
        int n = height.size();
        stack<int> s;
        int result = 0;
        
        int i = 0;
        while( i < n ) {
            
            if( s.empty() || height[i] >= height[s.top()] ) {
                s.push(i);
                i++;
            }
            else {
                int tp = s.top();
                s.pop();
                int h = height[tp];
                int w = (s.empty()) ? i : (i-s.top()-1);
                int area = h * w;
                result = max(result,area);
            }
            
        }
        
        while( !s.empty() ) {
            int tp = s.top();
            s.pop();
            
            int h = height[tp];
            int w = (s.empty()) ? i : (i - s.top() - 1);
            int area = h * w;
            result = max(area,result);
            
        }
        
        return result;
    }
};
```
