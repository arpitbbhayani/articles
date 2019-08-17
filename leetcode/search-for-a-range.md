```c
#include <algorithm>

class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        
        vector<int> v;
        
        int indexa = lower_bound(A,A+n,target) - A;
        int indexb = upper_bound(A,A+n,target) - A;
		
		if( indexa == n ) {
			v.push_back(-1);
			v.push_back(-1);
			return v;
		}
		
		if( A[indexb-1] == target  ) {
			v.push_back(indexa);
			v.push_back(indexb-1);
			return v;
		}
		
		v.push_back(-1);
        v.push_back(-1);
        return v;
		
    }
};
```
