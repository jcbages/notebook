/* Segment tree for kth order statistic in a range l...r */
struct node {
    int l, r, v;
    node() {l = r = -1, v = 0;}
    node(int _l, int _r, int _v) {l = _l, r = _r, v = _v;}
};
vector<node> segtree;
vector<int> roots, arr;

/* Initial build with 0 for all items */
int build(int l, int r) {
    if (l == r) {
        segtree.push_back(node());
        return segtree.size()-1;
    } else {
        int li = build(l, (l+r)/2);
        int ri = build((l+r)/2+1, r);
        segtree.push_back(node(li, ri, 0));
        return segtree.size()-1;
    }
}

/* Query the kth val if sorted in a range l...r */
int query(int l, int r, int a, int b, int k) {
    if (l == r) {
        return l;
    } else if (segtree[segtree[b].l].v-segtree[segtree[a].l].v >= k) {
        return query(l, (l+r)/2, segtree[a].l, segtree[b].l, k);
    } else {
        int nk = k-segtree[segtree[b].l].v+segtree[segtree[a].l].v;
        return query((l+r)/2+1, r, segtree[a].r, segtree[b].r, nk);
    }
}

int query(int l, int r, int k) {return query(1, LIM, roots[l-1], roots[r], k);}

/* Insert next item & add new nodes to segtree */
int insert(int l, int r, int i, int p) {
    if (l == r) {
        segtree.push_back(node(-1, -1, 1));
        return segtree.size()-1;
    } else {
        int li = segtree[i].l;
        int ri = segtree[i].r;
        if (p <= (l+r)/2) {
            li = insert(l, (l+r)/2, li, p);
        } else {
            ri = insert((l+r)/2+1, r, ri, p);
        }
        segtree.push_back(node(li, ri, segtree[li].v+segtree[ri].v));
        return segtree.size()-1;
    }
}

int insert(int i, int p) {return insert(1, LIM, roots[i], p);}

/* Initialize the segment tree & insert each arr item */
void init() {
    roots.push_back(build(1, LIM));
    for (int i = 0; i < arr.size(); ++i) {
        roots.push_back(insert(i, arr[i]));
    }
}