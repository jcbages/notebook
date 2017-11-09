/* Union Find container (negative is size) */
int uf[SIZE];

/* Find the component to which v belongs */
int find(int v) {return (uf[v] < 0) ? v : (uf[v] = find(uf[v]));}

/* Join components of u & v */
void join(int u, int v) {
    int pu = find(u), pv = find(v);
    if (uf[pu] > uf[pv]) swap(pu, pv);
    uf[pu] += uf[pv], uf[pv] = pu;
}

/* Initialize uf sizes (-1) */
void init() {memset(uf, 255, sizeof(uf));}