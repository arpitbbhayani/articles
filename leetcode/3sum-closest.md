```c
#include <algorithm>
#include <cmath>

class compar {
    bool operator()( int i, int j ) {
        return i < j;
    }
};

class Solution {
public:

    compar comparobject;

    int threeSumClosest(vector<int> &num, int target) {
        sort(num.begin(), num.end());

        int diff = INT_MAX;
        int ans = INT_MAX;

        for( int k = 0 ; k < num.size() ; k++ ) {

            int i = k+1, j = num.size()-1;

            while ( i < j ) {

                int localsum = num[i] + num[j] + num[k];
                int localdiff = abs(target - localsum);

                if( localdiff < diff ) {
                    diff = localdiff;
                    ans = localsum;
                }

                if( localsum < target ) {
                    i++;
                }
                else if ( localsum > target ) {
                    j--;
                }
                else {
                    break;
                }

            }
        }
        return ans;
    }
};
```
