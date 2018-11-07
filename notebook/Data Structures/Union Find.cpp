#include <bits/stdc++.h>
using namespace std;
#define SIZE 4

// union Find container (negative is size)
vector<int> uf(SIZE, -1);

// find the component to which v belongs
int find(int v) {
    return uf[v] < 0 ? v : uf[v] = find(uf[v]);
}

// merge components of u and v
void merge(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu == pv) {
        return;
    }
    if (-uf[pu] < -uf[pv]) {
        swap(pu, pv);
    }
    uf[pu] += uf[pv];
    uf[pv] = pu;
}

int main() {
    // merge 1 & 2 (sz = 2)
    merge(1, 2);
    assert(find(1) == find(2));
    cout << -uf[find(1)] << "\n";

    // merge 2 & 4 (sz = 3)
    merge(2, 4);
    assert(find(1) == find(4));
    cout << -uf[find(4)] << "\n";
}