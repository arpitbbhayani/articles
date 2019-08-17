```
class Solution {
public:

    int **array;

    int e(const char * str1, const char * str2, int l1, int l2) {
        
        if( array[l1][l2] != -1 ) {
            return array[l1][l2];
        }
        
        if( l1 == 0 && l2 == 0 ) {
            array[l1][l2] = 0;
            return 0;
        }
        
        if( l1 == 0 ) {
            array[l1][l2] = l2;
            return l2;
        }
        
        if( l2 == 0 ) {
            array[l1][l2] = l1;
            return l1;
        }
        
        int a = e(str1,str2,l1-1,l2) + 1;
        int b = e(str1,str2,l1,l2 - 1) + 1;
        int c = e(str1,str2,l1-1,l2-1) + ((str1[l1-1] == str2[l2-1])?0:1);
        
        array[l1][l2] = min(a,min(b,c));
        
        return min(a,min(b,c));
        
    }

    int minDistance(string word1, string word2) {
        const char * str1 = word1.c_str();
        const char * str2 = word2.c_str();
        
        int l1 = word1.length();
        int l2 = word2.length();
        
        array = (int **) malloc(sizeof(int *) * (l1+10));
        for( int i = 0 ; i < l1+10; i++ ) {
            array[i] = (int *) malloc(sizeof(int) * (l2+10));
        }
        
        for( int i = 0; i < l1+10; i++ ) {
            for(int j = 0 ; j < l2+10; j++) {
                array[i][j] = -1;
            }
        }
        
        return e(str1,str2, l1,l2);
    }
};
```
