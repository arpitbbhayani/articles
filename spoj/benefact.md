#include <iostream>
#include <queue>
#include <list>

using namespace std;

struct node {
	long long int cost;
	int d;
};

list<struct node *> nodes[50010];
int visited[50010];
long long int dist[50010];

int last_node ( int n , int source ) {

	queue<int> q;

	visited[source] = 1;
	dist[source] = 0;

	q.push(source);

	while ( !q.empty() ) {
		int parent = q.front();
		q.pop();

		for ( list<struct node *>::iterator itr = nodes[parent].begin() ; itr != nodes[parent].end() ; itr++ ) {

			int child = (*itr)->d;

			if ( visited[child] == 1 )
				continue;

			long long int t = dist[parent] + (*itr)->cost;

			if ( t > dist[child] )
				dist[child] = t;

			visited[child] = 1;
			q.push(child);
		}

	}

	long long int max = -1;
	int last_node = 0;
	for ( int i = 0 ; i < n ; i++) {

		//cout << "distance node " << i << " : " << dist[i] << endl;
		if ( dist[i] > max ) {
			last_node = i;
			max = dist[i];
		}
	}

	return last_node;
}

int main ( int argc , char * argv[] ) {

	int t;

	cin >> t;

	while ( t-- ) {
		int n;
		cin >> n;

		for ( int i = 0 ; i < n ; i++ ) {
			dist[i] = 0;
			visited[i] = 0;
			nodes[i].clear();
		}

		for( int i = 0 ; i < n-1 ; i++ ) {
			long long int a , b , c;
			cin >> a >> b >> c;

			struct node * n = new struct node;
			n -> d = b-1;
			n -> cost = c;
			nodes[a-1].push_back(n);

			struct node * m = new struct node;
			m -> d = a-1;
			m -> cost = c;
			nodes[b-1].push_back(m);

		}

		int last = last_node( n , 0 );

		for ( int i = 0 ; i < n ; i++ ) {
			visited[i] = 0;
			dist[i] = 0;
		}

		last = last_node( n , last );

		cout << dist[last] << endl;

	}

	return 0;
}
