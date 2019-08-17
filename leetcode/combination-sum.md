```c
class Solution {
public:

    vector<int> buffer;
    vector< vector<int> > ans;

    void print( vector<int> &array, int n, int k, int target, int index ) {
    
    	if( target < 0 ) {
    		return;
    	}
    
    	if( target == 0 ) {
    	    ans.push_back(buffer);
    		/*for(int i = 0 ; i < index ; i++ ) {
    			cout << buffer[i] << " ";
    		}*/
    		return;
    	}
    
    	for( int i = k ; i < n ; i++ ) {
    	    buffer.push_back(array[i]);
    		//buffer[index] = array[i];
    		print(array,n, i,target-array[i],index+1);
    		buffer.pop_back();
    	}
    
    }
    

    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(),candidates.end());
        print(candidates,candidates.size(),0,target,0);
        return ans;
    }
};
```
