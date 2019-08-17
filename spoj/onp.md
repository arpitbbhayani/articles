```c
/*
http://www.codechef.com/problems/ONP
*/

#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
using namespace std;

int precedence ( char c ) {

	switch ( c ) {
		case '(':
			return 1;
		case '+':
		case '-':
			return 2;
		case '*':
		case '/':
		case '^':
			return 3;
	}
	return 0;

}

int isop ( char c1 ) {
	if ( c1 == '(' || c1 == '+' || c1 == '-' || c1 == '*' || c1 == '/' || c1 == '^' )
		return 1;
	return 0;
}

void print(stack<char> &s) {
	if(s.empty()) {
       		cout << endl;
        	return;
    	}

	char x= s.top();
    	s.pop();
    	print(s);
    	s.push(x);
    	cout << x << " ";
}

int main ( int argc , char * argv[] ) {

	stack < char > s;
	string infix;
	int t;

	cin >> t;
	getchar();
	while ( t-- ) {	

		getline ( cin , infix );

		for ( int i = 0 ; i < infix.length() ; i++ ) {
			char ch = infix[i];
	
			if ( ch == '(' ) {
				s.push ( ch );
			}
			else if ( isalnum ( ch ) ) {
					cout << ch;
			}
			else if ( ch == ')' ) {
				while ( s.top() != '(' ) {
					cout << s.top();
					s.pop();
				}
				s.pop();
			}
			else if ( isop( ch ) ) {
	
				while ( !s.empty() && precedence ( s.top() ) >= precedence ( ch ) ) {
					cout << s.top();
					s.pop();
				}
				s.push(ch);
			}
		}
	
		while ( ! s.empty() ) {
			cout << s.top();
			s.pop();
		}
		cout << endl;
	}

	return 0;
}
```
