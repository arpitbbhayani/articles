#include <iostream>
#include <cstdio>
#include <map>
#include <set>

using namespace std;

int main ( int argc , char * argv[] ) {

	int t , n;
	cin >> t;

	n = t;
	map<int , set<int> > m;

	while ( t-- ) {

		int id;
		cin >> id;

		int k;
		cin >> k;
		while ( k-- ) {
			int l;
			cin >> l;
			m[id].insert(l);
		}
	}

	set<int> fof;

	for ( map<int,set<int> >::iterator itr = m.begin() ; itr != m.end() ; itr++ ) {
		//cout << "ID : " << itr->first << endl;
		for ( set<int>::iterator itr_c = (itr->second).begin() ; itr_c != (itr->second).end() ; itr_c++ ) {
			//cout << "\t" << *itr_c << endl;
			if ( m.count(*itr_c) == 0 )
				fof.insert(*itr_c);
		}
	}

	cout << fof.size() << endl;

	return 0;

}
