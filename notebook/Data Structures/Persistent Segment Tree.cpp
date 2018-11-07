#include <bits/stdc++.h>
using namespace std;
#define MAXNUM 9

// segment tree for kth order statistic in a range l...r
// this one assumes each number in the array is unique
// in case numbers are too large or duplicate, compress coords
struct node {
    int l, r, v;
    node() { }
    node(int _l, int _r, int _v) {
        l = _l, r = _r, v = _v;
    }
};
vector<node> segtree;
vector<int> roots;

// initial build with 0 for all items
int build(int l, int r) {
    if (l == r) {
        segtree.push_back(node(-1, -1, 0));
        return segtree.size()-1;
    } else {
        int mid = (l+r)/2;
        int li = build(l, mid);
        int ri = build(mid+1, r);
        segtree.push_back(node(li, ri, 0));
        return segtree.size()-1;
    }
}

// query the kth val if sorted in range rep by segtrees [p1...p2]
int query(int l, int r, int p1, int p2, int K) {
    int mid = (l+r)/2;
    if (l == r) {
        return l;
    }
    int v1 = segtree[segtree[p1].l].v;
    int v2 = segtree[segtree[p2].l].v;
    if (v2-v1 >= K) {
        return query(l, mid, segtree[p1].l, segtree[p2].l, K);
    } else {
        return query(mid+1, r, segtree[p1].r, segtree[p2].r, K-v2+v1);
    }
}

int query(int l, int r, int K) {
    return query(1, MAXNUM, roots[l-1], roots[r], K);
}

// insert next item & add new nodes to segtree
int insert(int l, int r, int i, int p) {
    if (l == r) {
        segtree.push_back(node(-1, -1, 1));
        return segtree.size()-1;
    } else {
        int mid = (l+r)/2;
        int lpos = segtree[i].l;
        int rpos = segtree[i].r;
        if (p <= mid) {
            lpos = insert(l, mid, lpos, p);
        } else {
            rpos = insert(mid+1, r, rpos, p);
        }
        segtree.push_back(node(lpos, rpos, segtree[lpos].v+segtree[rpos].v));
        return segtree.size()-1;
    }
}

int insert(int i, int p) {
    return insert(1, MAXNUM, roots[i], p);
}

int main() {
    int arr[] = {6, 5, 4, 3, 8, 7, 1, 3, 2};    

    // initialize segtrees
    roots.push_back(build(1, MAXNUM));
    for (int i = 0; i < MAXNUM; ++i) {
        roots.push_back(insert(i, arr[i]));
    }

    // query kth order for ranges -- 4, 7, 8
    cout << query(1, 9, 4) << "\n";
    cout << query(5, 9, 3) << "\n";
    cout << query(3, 5, 3) << "\n";
}