#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

#define FOR(I,A,B)	for(int I = (A); I < (B); ++I)
#define REP(I,N)	FOR(I,0,N)
#define ALL(A)		(A).begin(), (A).end()

using namespace std;

int main(){
  int n;
  cin >> n;
  while(n--){

    string tmp;
    cin >> tmp;

    vector<int> numbers;
    vector<char> operators;

    FOR(i, 0, tmp.size()){
	if(i % 2 == 0){
	    numbers.push_back(atoi(&tmp[i]));
	} else {
	    operators.push_back(tmp[i]);
	}
    }

    vector< vector<long long> > min_costs(numbers.size() + 1, vector<long long>(numbers.size() + 1, numeric_limits<int>::max()));
    vector< vector<long long> > max_costs(numbers.size() + 1, vector<long long>(numbers.size() + 1, 0));
    FOR(i, 0, numbers.size() + 1){ max_costs[i][i] = min_costs[i][i] = numbers[i]; }

    int numbers_total = numbers.size();
    FOR(l, 2, numbers_total + 1){
      FOR(i, 0, numbers_total - l + 1){
        int j = i + l - 1;
        FOR(k, i, j){
	  int min_tmp = 0;
	  int max_tmp = 0;
	  if(operators[k] == '+'){
              min_tmp = min_costs[i][k] + min_costs[k+1][j];
              max_tmp = max_costs[i][k] + max_costs[k+1][j];
	  }else if(operators[k] == '*'){
              min_tmp = min_costs[i][k] * min_costs[k+1][j];
              max_tmp = max_costs[i][k] * max_costs[k+1][j];
	  }
          if(min_tmp < min_costs[i][j]){
            min_costs[i][j] = min_tmp;
          }
          if(max_tmp > max_costs[i][j]){
            max_costs[i][j] = max_tmp;
          }
        }
      }
    }
    cout << max_costs[0][numbers_total-1] << " " << min_costs[0][numbers_total-1] << endl;
  }
}
