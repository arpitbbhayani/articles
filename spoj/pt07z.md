#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>

#define DEBUG 0

using namespace std;

long int dist[10010];

// returns the last element
int bfs ( vector<int> node[] , int n , int start ) {

	int visited[n+1];

	for ( int i = 0 ; i < n+1 ; i++ )
		visited[i] = 0;

	visited[0] = 1;

	queue<int> q;
	q.push(start);

	visited[start] = 1;
	dist[start] = 0;

	while ( !q.empty() ) {
		int parent = q.front();
		q.pop();

		for ( vector<int>::iterator itr = node[parent].begin() ; itr != node[parent].end() ; itr++ ) {
			int child = *itr;

			if ( visited[child] == 1 )
				continue;

			dist[child] = 1 + dist[parent];

			visited[child] = 1;
			q.push(child);
		}
	}

	long int max = -1;
	int last = 1;
	for ( int i = 0 ; i < n+1 ; i++ ) {
		if ( dist[i] > max ) {
			max = dist[i];
			last = i;
		}
	}

	return last;
}

int main ( int argc ,char * argv[] ) {

	int n;
	scanf("%d" , &n );

	vector<int> node[n+1];

	for ( int i = 0 ; i < n-1 ; i++ ) {
		int u,v;
		scanf("%d%d" , &u,&v);
		node[u].push_back(v);
		node[v].push_back(u);
	}

	#if DEBUG
		printf("Adjecency List\n");
		for ( int i = 0 ; i < n+1 ; i++ ) {
			printf("Node %d : " , i);
			for ( vector<int>::iterator itr = node[i].begin() ; itr != node[i].end() ; itr++ ) {
				printf("%d " , *itr);
			}
			printf("\n");
		}
	#endif

	for ( int i = 0 ; i < n+1 ; i++ )
		dist[i] = 0;

	int last_node = bfs( node , n , 1 );

	#if DEBUG
		printf("Last node after 1st BFS : %d\n" , last_node);
	#endif

	for ( int i = 0 ; i < n+1 ; i++ )
		dist[i] = 0;

	last_node = bfs(node , n , last_node );

	#if DEBUG
		printf("Last node after 2nd BFS : %d\n" , last_node);
	#endif

	printf("%ld\n" ,  dist[last_node]);

	return 0;
}
