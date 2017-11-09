/* Segment tree for swapping & counting items color in range */
struct node {
	int lazy, black, white;
	node() {lazy = black = white = 0;}
} segtree[3*SIZE];

/* Initial build, all values are white */
void build(int i, int l, int r) {
    if (l == r) {
        segtree[i].white = 1;
    } else {
        build(2*i, l, (l+r)/2);
        build(2*i+1, (l+r)/2+1, r);
        segtree[i].white = segtree[2*i].white+segtree[2*i+1].white;
    }
}

/* Lazy propagation function for visited nodes */
void lazyprop(int i, int l, int r) {
    if (l < r) {
        segtree[2*i].lazy += segtree[i].lazy;
        segtree[2*i+1].lazy += segtree[i].lazy;
    }
    if (segtree[i].lazy%2 != 0) {
        swap(segtree[i].white, segtree[i].black);
    }
    segtree[i].lazy = 0;
}

/* Query the # of black items in a range a...b */
int query(int i, int l, int r, int a, int b) {
    lazyprop(i, l, r);
    if (a <= l && r <= b) return segtree[i].black;
    if (b < l || a > r) return 0;
    int v1 = query(2*i, l, (l+r)/2, a, b);
    int v2 = query(2*i+1, (l+r)/2+1, r, a, b);
    return v1+v2;
}

int query(int l, int r) {return query(1, 1, SIZE, l, r);}

/* Swap all items color in a range a...b */
void update(int i, int l, int r, int a, int b) {
    lazyprop(i, l, r);
    if (a <= l && r <= b) {
        ++segtree[i].lazy;
        lazyprop(i, l, r);
    } else if (!(b < l || a > r)) {
        update(2*i, l, (l+r)/2, a, b);
        update(2*i+1, (l+r)/2+1, r, a, b);
        segtree[i].white = segtree[2*i].white+segtree[2*i+1].white;
        segtree[i].black = segtree[2*i].black+segtree[2*i+1].black;
    }
}

void update(int p, int v) {update(1, 1, SIZE, p, v);}