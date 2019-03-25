#include<bits/stdc++.h>
using namespace std;
struct Edge {
	int v, flow, C, rev;
};
class Graph {
	int V; // number of vertex
	int *level ; // stores level of a node
	vector< Edge > *adj;
public :
	Graph(int V) {
		adj = new vector<Edge>[V];
		this->V = V;
		level = new int[V];
	}
	void addEdge(int u, int v, int C) {
		Edge a{v, 0, C, adj[v].size()}; // Forward edge : 0 flow and C capacity
		Edge b{u, 0, 0, adj[u].size()}; // Back edge : 0 flow and 0 capacity
		adj[u].push_back(a); adj[v].push_back(b);
	}
	bool BFS(int s, int t);
	int sendFlow(int s, int flow, int t, int ptr[]);
	int DinicMaxflow(int s, int t);
};
bool Graph::BFS(int s, int t) {
	for (int i = 0 ; i < V ; i++) level[i] = -1;
	level[s] = 0;
	list< int > q;
	q.push_back(s);
	vector<Edge>::iterator i ;
	while (!q.empty()) {
		int u = q.front();
		q.pop_front();
		for (i = adj[u].begin(); i != adj[u].end(); i++) {
			Edge &e = *i;
			if (level[e.v] < 0 && e.flow < e.C) {
				level[e.v] = level[u] + 1;
				q.push_back(e.v);
			}
		}
	}
	return level[t] < 0 ? false : true; // can we reach sink
}
// t : Sink, start[]: start[i] stores count of edges explored from i.
int Graph::sendFlow(int u, int flow, int t, int start[]) {
	if (u == t) return flow;
	for ( ; start[u] < adj[u].size(); start[u]++) {
		Edge &e = adj[u][start[u]];
		if (level[e.v] == level[u]+1 && e.flow < e.C) {
			int curr_flow = min(flow, e.C - e.flow);
			int temp_flow = sendFlow(e.v, curr_flow, t, start);
			if (temp_flow > 0) {
				e.flow += temp_flow;
				adj[e.v][e.rev].flow -= temp_flow; // subs flow from rev edge of current
				return temp_flow;
			}
		}
	}
	return 0;
}
int Graph::DinicMaxflow(int s, int t) {
	if (s == t) return -1;
	int total = 0; // Initialize result
	while (BFS(s, t) == true) { // Augment the flow while there is path
		int *start = new int[V+1]; // store how many edges are visited from V {0toV}
		while (int flow = sendFlow(s, INT_MAX, t, start)) total += flow;
	}
	return total;
}
int main() {
	Graph g(6);g.addEdge(0,1,16);g.addEdge(0,2,13);g.addEdge(1,2,10);
  g.addEdge(1,3,12);g.addEdge(2,1,4);g.addEdge(2,4,14);g.addEdge(3,2,9);
  g.addEdge(3,5,20);g.addEdge(4,3,7);g.addEdge(4,5,4);
  cout << "Maximum flow " << g.DinicMaxflow(0, 5);
	return 0;
}
