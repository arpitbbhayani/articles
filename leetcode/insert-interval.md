```
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        
        if( intervals.size() == 0 ) {
            intervals.push_back(newInterval);
            return intervals;
        }
        
        int i = 0;
        while( i < intervals.size() && intervals[i].start < newInterval.start ) {
            i++;
        }
        intervals.insert(intervals.begin() + i, newInterval);
        
        
        stack<Interval> s;
        
        s.push(intervals[0]);
        
        for( int i = 1 ; i < intervals.size(); i++ ) {
            
            Interval curr = intervals[i];
            Interval ons = s.top();
            
            
            if( curr.start > ons.end ) {
                s.push(curr);
            }
            else {
                if( curr.end > ons.end ) {
                    
                    ons.end = curr.end;
                    
                    s.pop();
                    s.push(ons);
                }
            }
            
        }
        
        intervals.clear();
        while( s.empty() == false ) {
            intervals.insert(intervals.begin(),s.top());
            s.pop();
        }
        
        return intervals;
        
    }
};
```
