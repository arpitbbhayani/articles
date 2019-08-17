```c
#include <iostream>
#include <list>
#include <climits>
#include <cstdio>

using namespace std;

struct node {
	int node_number;
	int cost;
};

void create_graph ( int r , int c , list<struct node *> * list_ ) {
	int a = r * 8 + c;

	int n , m;

	n = r + 2; m = c + 1;
	if ( n >= 0 && n <= 7 && m >= 0 && m <= 7 ) {
		struct node * nd = new struct node;
		nd->node_number = n*8 + m;
		nd->cost = r*n + c*m;
		list_[a].push_back(nd);
	}
	n = r + 2; m = c - 1;
	if ( n >= 0 && n <= 7 && m >= 0 && m <= 7 ) {
		struct node * nd = new struct node;
		nd->node_number = n*8 + m;
		nd->cost = r*n + c*m;
		list_[a].push_back(nd);
	}
	n = r - 2; m = c + 1;
	if ( n >= 0 && n <= 7 && m >= 0 && m <= 7 ) {
		struct node * nd = new struct node;
		nd->node_number = n*8 + m;
		nd->cost = r*n + c*m;
		list_[a].push_back(nd);
	}
	n = r - 2; m = c - 1;
	if ( n >= 0 && n <= 7 && m >= 0 && m <= 7 ) {
		struct node * nd = new struct node;
		nd->node_number = n*8 + m;
		nd->cost = r*n + c*m;
		list_[a].push_back(nd);
	}
	n = r + 1; m = c + 2;
	if ( n >= 0 && n <= 7 && m >= 0 && m <= 7 ) {
		struct node * nd = new struct node;
		nd->node_number = n*8 + m;
		nd->cost = r*n + c*m;
		list_[a].push_back(nd);
	}
	n = r + 1; m = c - 2;
	if ( n >= 0 && n <= 7 && m >= 0 && m <= 7 ) {
		struct node * nd = new struct node;
		nd->node_number = n*8 + m;
		nd->cost = r*n + c*m;
		list_[a].push_back(nd);
	}
	n = r - 1; m = c + 2;
	if ( n >= 0 && n <= 7 && m >= 0 && m <= 7 ) {
		struct node * nd = new struct node;
		nd->node_number = n*8 + m;
		nd->cost = r*n + c*m;
		list_[a].push_back(nd);
	}
	n = r - 1; m = c - 2;
	if ( n >= 0 && n <= 7 && m >= 0 && m <= 7 ) {
		struct node * nd = new struct node;
		nd->node_number = n*8 + m;
		nd->cost = r*n + c*m;
		list_[a].push_back(nd);
	}
	
}

int dijkstra ( int s , int t , list<struct node *> *list_ ) {

	int dist[64];
	int visited[64];

	for ( int i = 0 ; i < 64 ; i++ ) {
		dist[i] = INT_MAX;
		visited[i] = 0;
	}

	dist[s] = 0;

	while ( s != -1 ) {

		visited[s] = 1;

		for ( list<struct node *>::iterator itr = list_[s].begin() ; itr != list_[s].end() ; itr++ ) {
			struct node * v = (*itr);
			if ( visited[v->node_number] == 1 )
				continue;

			if ( dist[v->node_number] > dist[s] + v->cost ) {
				dist[v->node_number] = dist[s] + v->cost;
			}
		}

		s = -1;
		int min_distance = INT_MAX;
		for ( int i = 0 ; i < 64 ; i++ ) {
			if ( visited[i] == 0 && dist[i] < min_distance ) {
				s = i;
				min_distance = dist[i];
			}
		}

	}

	return dist[t];

}

int main ( int argc , char * argv[] ) {

	list<struct node *> * list_ = new list<struct node *>[64];

	for ( int i = 0 ; i < 8 ; i ++ ) {
		for ( int j = 0 ;  j < 8 ; j++ ) {
			create_graph( i , j , list_ );
		}
	}

	/*for ( int i = 0 ; i < 64 ; i++ ) {
		cout << "Node " << i << " : ";
		for ( list<struct node *>::iterator itr = list_[i].begin() ; itr != list_[i].end() ; itr++ ) {
			cout << " " << (*itr)->node_number;
		}
		cout << endl;
	}*/

	int r1,c1,r2,c2;
	while ( scanf("%d%d%d%d" , &r1 , &c1 , &r2 , &c2 ) != EOF ) {
		cout << dijkstra ( r1 * 8 + c1 , r2 * 8 + c2 , list_ ) << endl;
	}

	return 0;
}
```
