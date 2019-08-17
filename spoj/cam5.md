#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

int main ( int argc , char * argv[] ) {

	int t;

	cin >> t;

	while ( t-- ) {
		int n;
		cin >> n;

		list<int> node[n];
		int visited[n];

		int p;
		cin >> p;

		for ( int i = 0 ; i < n ; i++ ) {
			visited[i] = 0;

			/*cout << "Node : " << i << " -> ";
			for ( vector<int>::iterator itr = node[i].begin() ; itr != node[i].end() ; itr++ ) {
				cout << *itr << " ";
			}
			cout << endl;
			*/

		}


		while ( p-- ) {
			int a , b;
			cin >> a >> b;

			node[a].push_back(b);
			node[b].push_back(a);
		}

		
		queue<int> q;
		int count = 0;
		for ( int i = 0 ; i < n ; i++ ) {

			if ( visited[i] == 1 )
				continue;

			visited[i] = 1;

			q.push(i);

			while ( !q.empty() ) {
				int t = q.front();
				q.pop();

				for ( list<int>::iterator itr = node[t].begin() ; itr != node[t].end() ; itr++ ) {
					int child = *itr;

					if ( visited[child] == 1 )
						continue;

					visited[child] = 1;
					q.push(child);
				}
				
			}

			count ++;
			

		}

		cout << count << endl;


	}

	return 0;

}
