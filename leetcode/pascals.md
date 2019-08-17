class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        
        vector< vector<int> > v;
        
        if( numRows == 0 ) {
            return v;
        }
        
        vector<int> t,u;
        t.push_back(1);
        v.push_back(t);
        
        for( int i = 1 ; i < numRows ; i++ ) {
            t = v[i-1];
            u.clear();
            int sum = 0;
            for( int j = 0 ; j < i ; j++ ) {
                u.push_back(sum+t[j]);
                sum = t[j];
            }
            u.push_back(1);
            v.push_back(u);
        }
        return v;
    }
};
