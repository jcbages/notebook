// solution to problem kill the werewolf latin america icpc 2015
// maybe ignore main, important part in cannot_win procedure

#include <bits/stdc++.h>
using namespace std;
#define MAX 110
#define INF 100000000
#define max(a, b) (((a)>(b))?(a):(b))
#define min(a, b) (((a)<(b))?(a):(b))

bool e[MAX][MAX]; // adj matrix e[u][v] = true iff edge (u,v)
int n, votes[MAX][2], freq[MAX];
int g[MAX][MAX]; // adj matrix of capacity of each edge
int f[MAX][MAX]; // adj matrix of flow going through each edge
int p[MAX]; // parents of each node (used by bfs)
int m[MAX]; // flow thourgh each node (used by bfs)

int bfs() {
	for (int u = 0; u < MAX; u++) { // initialize flow entering each node & parents
        m[u] = INF; p[u] = -1;
  }
  // do the bfs procedure from source s (0)
	queue<int> q;
  q.push(0);
	while (q.size() > 0) {
		int u = q.front(); q.pop();
		for (int v = 1; v <= 2*n+1; v++) {
      // check if neighbors, capacity is > 0 & not visited yet
			if (e[u][v] && g[u][v]-f[u][v] > 0 && p[v] == -1) {
				// update parent and flow going through node v
				p[v] = u;
        m[v] = min(m[u], g[u][v]-f[u][v]);
        q.push(v);
        // finish if sink was reached
				if (v == 2*n+1) return m[v];
			}
		}
	}
  // no augmenting path found, return 0
	return 0;
}

bool cannot_win() {
	int req = 0, tot = 0, curr, v;
	for (int u = 1; u <= n; u++) {
      req += g[0][u];
  }
  // clean flow as initially its 0
	for (int u = 0; u < MAX; u++) {
      memset(f[u], 0, sizeof(f[u]));
  }
  // while there are augmenting paths
	while ((curr = bfs()) > 0) {
		tot += curr; // add flow found on curr path
    v = 2*n+1; // this is the sink
		while (v != 0) {
            f[p[v]][v] += curr; // increase flow f(u, v) by curr
            f[v][p[v]] -= curr; // decrease flow f(v, u) by curr
            v = p[v]; // go back until source
        }
	}
	return (req == tot);
}

int main() {
	iostream::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	memset(freq, 0, sizeof(freq));
	for (int u = 1; u <= n; u++) {
		cin >> votes[u][0] >> votes[u][1];
		freq[votes[u][0]]++, freq[votes[u][1]]++;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
    // this is the graph construction part
		for (int u = 0; u < MAX; u++) {
			memset(g[u], 0, sizeof(g[u]));
			memset(e[u], false, sizeof(e[u]));
		}
		for (int u = 1; u <= n; u++) {
			g[0][u] = (u != i && votes[u][0] != i && votes[u][1] != i);
			e[0][u] = e[u][0] = g[0][u];
		}
		for (int u = 1; u <= n; u++) {
			for (int v = 1; v <= n; v++) {
				g[u][v+n] = (votes[u][0] == v || votes[u][1] == v);
				e[u][v+n] = e[v+n][u] = g[u][v+n];
			}
		}
		for (int u = 1; u <= n; u++) {
			e[u+n][2*n+1] = e[2*n+1][u+n] = true;
			g[u+n][2*n+1] = freq[i]-1-(votes[i][0] == u || votes[i][1] == u);
		}
    // this is the maxflow calculation part
		ans += cannot_win();
	}
	cout << n-ans << '\n';
}
