/* Segment tree for sum in a very large range (LIM=10^9) */
struct node {
    int l, r, v;
    node() {l = r = -1, v = 0;}
};
vector<node> segtree;

/* Initial build with 0 for all items */
void build() {
    segtree.push_back(node());
}

/* Query the sum in a range a...b */
int query(int i, int l, int r, int a, int b) {
    if (i == -1 || b < l || a > r) {
        return 0;
    } else if (a <= l && r <= b) {
        return segtree[i].v;
    } else {
        int v1 = query(segtree[i].l, l, (l+r)/2, a, b);
        int v2 = query(segtree[i].r, (l+r)/2+1, r, a, b);
        return v1+v2;
    }
}

int query(int l, int r) {return query(0, 1, LIM, l, r);}

/* Add a node for complement the traversing path */
int add_node() {
    segtree.push_back(node());
    return segtree.size()-1;
}

/* Add v to item in position p */
void update(int i, int l, int r, int p, int v) {
    if (l == r) {
        segtree[i].v += v;
    } else {
        if (p <= (l+r)/2) {
            if (segtree[i].l == -1) segtree[i].l = add_node();
            update(segtree[i].l, l, (l+r)/2, p, v);
        } else {
            if (segtree[i].r == -1) segtree[i].r = add_node();
            update(segtree[i].r, (l+r)/2+1, r, p, v);
        }
        int v1 = (segtree[i].l == -1) ? 0 : segtree[segtree[i].l].v;
        int v2 = (segtree[i].r == -1) ? 0 : segtree[segtree[i].r].v;
        segtree[i].v = v1+v2;
    }
}

void update(int p, int v) {update(0, 1, LIM, p, v);}