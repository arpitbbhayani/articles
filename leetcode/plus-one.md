```
class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        int n = digits.size();
        int sum = 0;
        int carry = 1;
        for( int i = n-1 ; i >= 0 ; i-- ) {
            sum = (carry + digits[i]) % 10;
            carry = (carry + digits[i]) / 10;
            digits[i] = sum;
        }
        if( carry == 0 ) {
            return digits;
        }
        else {
            digits.insert(digits.begin(),carry);
            return digits;
        }
    }
};
```
