```c
class Solution {
public:

    int **hash;

    int _is( string a, string b, string c, int ia, int ib, int ic, int la, int lb, int lc ) {

        if( hash[ia][ib] != -1 ) {
            return hash[ia][ib];
        }

    	if( ia == la && ib == lb && ic == lc ) {
    	    hash[ia][ib] = 1;
    		return 1;
    	}
    
    	if( ia == la && ib == lb && ic != lc ) {
    	    hash[ia][ib] = 0;
    		return 0;
    	}
    	
    	int flag1 = 0, flag2 = 0;
    	if( a[ia] == c[ic] ) {
    		flag1 = _is(a,b,c,ia+1,ib,ic+1,la,lb,lc);
    	}
    	
    	if( b[ib] == c[ic] ) {
    		flag2 = _is(a,b,c,ia,ib+1,ic+1,la,lb,lc);
    	}
    	
    	hash[ia][ib] = flag1 || flag2;
    	return flag1 || flag2;

    }

    bool isInterleave(string s1, string s2, string s3) {
        int la = s1.length();
    	int lb = s2.length();
    	int lc = s3.length();
    	
    	if( la + lb != lc ) {
    		return 0;
    	}
    	
    	if( la == 0 && lb == 0 && lc == 0 ) {
    	    return 1;
    	}
    	
    	hash = (int **) malloc(sizeof(int *) * (la+10));
    	for( int i = 0 ; i < la+10; i++ ) {
    	    hash[i] = (int *) malloc(sizeof(int) * (lb+10));
    	}
    	
    	for( int i = 0 ; i < (la+10) ; i++ ) {
    	    for(int j = 0 ; j < (lb+10) ; j++ ) {
    	        hash[i][j] = -1;
    	    }
    	}

    	return _is(s1,s2,s3,0,0,0,la,lb,lc);
    }
};
```
