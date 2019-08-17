class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        
        int n = num.size();
		
        vector<int> temp;
        vector< vector<int> > ans;
        
        sort(num.begin(), num.end());
		
        for(int i = 0 ; i < (n - 2) ; i++ ) {
            if( i != 0 && num[i] == num[i-1] ) {
                continue;
            }
            
            int j = i + 1, k = n - 1;
            
            while ( j < k ) {
            
                int sum = num[i] + num[j] + num[k];
                
                if( sum == 0 ) {
                    temp.clear();
                    temp.push_back(num[i]);
                    temp.push_back(num[j]);
                    temp.push_back(num[k]);
                    ans.push_back(temp);
                    
                    j++;
                    k--;
                    
                    while( j < k && num[k] == num[k+1]) {
                        k--;
                    }
                    
                    while(j < k && num[j] == num[j-1] ) {
                        j++;
                    }
                    
                    
                }
                else if( sum < 0 ) {
                    j++;
                }
                else {
                    k--;
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
        
        
        /*for( set< vector<int> >::iterator itr = s.begin() ; itr != s.end() ; itr++ ) {
            ans.push_back(*itr);
        }*/
        
        return ans;
    }
};
