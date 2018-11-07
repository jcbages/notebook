#include <bits/stdc++.h>
using namespace std;
#define SIZE 1000000000

// segtree for sum in a very large range (SIZE=10^9)
struct node {
    int l, r, v;
    node() {
        l = r = -1;
        v = 0;
    }
};
vector<node> segtree;

// initial build with 0 for all items
void build() {
    segtree.push_back(node());
}

// query the sum in a range [a...b]
int query(int i, int l, int r, int a, int b) {
    if (i == -1 || b < l || a > r) {
        return 0;
    } else if (a <= l && r <= b) {
        return segtree[i].v;
    } else {
        int mid = (l+r)/2;
        int v1 = query(segtree[i].l, l, mid, a, b);
        int v2 = query(segtree[i].r, mid+1, r, a, b);
        return v1+v2;
    }
}

int query(int l, int r) {
    return query(0, 1, SIZE, l, r);
}

// add a node to complement the traversing path
int add_node() {
    segtree.push_back(node());
    return segtree.size()-1;
}

// Add v to item in position p
void update(int i, int l, int r, int p, int v) {
    if (l == r) {
        segtree[i].v += v;
    } else {
        int mid = (l+r)/2;
        if (p <= mid) {
            if (segtree[i].l == -1) {
                int pos = add_node();
                segtree[i].l = pos;
            }
            update(segtree[i].l, l, mid, p, v);
        } else {
            if (segtree[i].r == -1) {
                int pos = add_node();
                segtree[i].r = pos;
            }
            update(segtree[i].r, mid+1, r, p, v);
        }
        int v1 = segtree[i].l == -1 ? 0 : segtree[segtree[i].l].v;
        int v2 = segtree[i].r == -1 ? 0 : segtree[segtree[i].r].v;
        segtree[i].v = v1+v2;
    }
}

void update(int p, int v) {
    update(0, 1, SIZE, p, v);
}

int main() {
    // initialize the segtree
    build();

    // add some values to the tree
    update(10, 150);
    update(1000, 150);
    update(100000000, 150);

    // query some values from the tree -- 300, 150, 450
    cout << query(1, 1000000) << "\n";
    cout << query(1001, 100000000) << "\n";
    cout << query(9, 1000000000) << "\n";
}