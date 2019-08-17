```c
class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        
        map<int,int> m;
        int n = num.size();
        
    	for( int i = 0 ; i < n ; i++ ) {
    		m[num[i]] = 1;
    	}
    	
    	for( map<int,int>::iterator itr = m.begin(); itr != m.end(); itr++ ) {
    		int a = itr->first;
    		if( m.find(a-1) != m.end() ) {
    			itr->second = m[a-1] + 1;
    		}
    	}
    	
    	int m1 = INT_MIN;
    	for( map<int,int>::iterator itr = m.begin(); itr != m.end(); itr++ ) {
    		m1 = max(m1,itr->second);
    	}
    	
    	return m1;
    }
};
```
