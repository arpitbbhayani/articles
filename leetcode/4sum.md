```
class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
        
        set< vector<int> >s;
        
        int n = num.size();
		
        vector<int> temp;
        vector< vector<int> > ans;
        
        sort(num.begin(), num.end());
		
        for(int i = 0 ; i < (n - 3) ; i++ ) {
		
			for( int j = i+1 ; j < n-2 ; j++ ) {
			
				int k = j + 1, l = n - 1;
            
				while ( k < l ) {
				
					int sum = num[i] + num[j] + num[k] + num[l];
					
					if( sum == target ) {
						temp.clear();
						temp.push_back(num[i]);
						temp.push_back(num[j]);
						temp.push_back(num[k]);
						temp.push_back(num[l]);
						s.insert(temp);
						
						k++;
						l--;
						
						while( k < l && num[l] == num[l+1]) {
							l--;
						}
						
						while(k < l && num[k] == num[k-1] ) {
							k++;
						}
						
						
					}
					else if( sum < target ) {
						k++;
					}
					else {
						l--;
					}
				}
			}
        }
        
        /*for( int i = ans.size() - 1 ; i >= 0 ; i-- ) {
            
            for( int j = i - 1 ; j >= 0 ; j-- ) {
                
                if( ans[i][0] == ans[j][0] && ans[i][1] == ans[j][1] && ans[i][2] == ans[j][2] ) {
                    ans.erase(ans.begin() + j);
                }
            }
        }*/
        
        
        for( set< vector<int> >::iterator itr = s.begin() ; itr != s.end() ; itr++ ) {
            ans.push_back(*itr);
        }
        
        return ans;
        
    }
};
```
