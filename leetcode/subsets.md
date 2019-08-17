```
class Solution {
public:

    vector<int> temp;
    vector< vector<int> > ans;


    void print(vector<int> &S, int index, int end) {
        if( index == end ) {
            return;
        }
        
        temp.push_back(S[index]);
        ans.push_back(temp);
        print(S,index+1,end);
        temp.pop_back();
    }

    vector<vector<int> > subsets(vector<int> &S) {
        
        sort(S.begin(), S.end());
        int len = 1 << S.size();
        
        for( int i = 0 ; i < len ; i++ ) {
            
            for( int j = 0 ;  j < S.size() ; j++ ) {
                
                if( i & (1 << j) ) {
                    temp.push_back(S[j]);
                }
                
            }
            
            ans.push_back(temp);
            temp.clear();
            
        }
        
        return ans;
    }
};
```
