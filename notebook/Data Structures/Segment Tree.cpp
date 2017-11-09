/* Segment tree for RMQ */
int segtree[3*SIZE], arr[SIZE];

/* Initial build & assignment of values */
void build(int i, int l, int r) {
    if (l == r) {
        segtree[i] = arr[l-1];
    } else {
        build(2*i, l, (l+r)/2);
        build(2*i+1, (l+r)/2+1, r);
        segtree[i] = min(segtree[2*i], segtree[2*i+1]);
    }
}

/* Query the min in a range a...b */
int query(int i, int l, int r, int a, int b) {
    if (a <= l && r <= b) {
        return segtree[i];
    } else if (b < l || a > r) {
        return INF;
    } else {
        int v1 = query(2*i, l, (l+r)/2, a, b);
        int v2 = query(2*i+1, (l+r)/2+1, r, a, b);
        return min(v1, v2);
    }
}

int query(int l, int r) {return query(1, 1, SIZE, l, r);}

/* Set item in position p to have value v */
void update(int i, int l, int r, int p, int v) {
    if (l == r) {
        segtree[i] = v;
    } else {
        if (p <= (l+r)/2) {
            update(2*i, l, (l+r)/2, p, v);
        } else {
            update(2*i+1, (l+r)/2+1, r, p, v);
        }
        segtree[i] = min(segtree[2*i], segtree[2*i+1]);
    }
}

void update(int p, int v) {update(1, 1, SIZE, p, v);}