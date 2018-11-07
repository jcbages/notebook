#include <bits/stdc++.h>
using namespace std;
#define SIZE 100000
#define SEGTREE (((int)log2(SIZE))+2)

// segtree for swapping & counting items color in range
struct node {
	int lazy, black, white;
	node() {
        lazy = black = white = 0;
    }
};

vector<node> segtree(1<<SEGTREE);

// initial build, all values are white
void build(int i, int l, int r) {
    if (l == r) {
        segtree[i].white = 1;
    } else {
        int mid = (l+r)/2;
        build(2*i, l, mid);
        build(2*i+1, mid+1, r);
        segtree[i].white = segtree[2*i].white+segtree[2*i+1].white;
    }
}

void build() {
    build(1, 1, SIZE);
}

// lazy propagation function for visited nodes
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

// query the number of black items in range [a...b]
int query(int i, int l, int r, int a, int b) {
    lazyprop(i, l, r);
    if (b < l || a > r) {
        return 0;
    } else if (a <= l && r <= b) {
        return segtree[i].black;
    } else {
        int mid = (l+r)/2;
        int v1 = query(2*i, l, mid, a, b);
        int v2 = query(2*i+1, mid+1, r, a, b);
        return v1+v2;
    }
}

int query(int l, int r) {
    return query(1, 1, SIZE, l, r);
}

// swap all items color in range [a...b]
void update(int i, int l, int r, int a, int b) {
    lazyprop(i, l, r);
    if (b < l || a > r) {
        return;
    } else if (a <= l && r <= b) {
        ++segtree[i].lazy;
        lazyprop(i, l, r);
    } else {
        int mid = (l+r)/2;
        update(2*i, l, mid, a, b);
        update(2*i+1, mid+1, r, a, b);
        segtree[i].white = segtree[2*i].white+segtree[2*i+1].white;
        segtree[i].black = segtree[2*i].black+segtree[2*i+1].black;
    }
}

void update(int l, int r) {
    update(1, 1, SIZE, l, r);
}

int main() {
    // initialize the segtree
    build();

    // update some items in range
    update(1, 7);
    update(100000, 100000);
    update(1000, 10000);
    update(9500, 10001);

    // query some items in range -- 5, 8509, 4501
    cout << query(3, 999) << "\n";
    cout << query(1, 100000) << "\n";
    cout << query(5000, 10500) << "\n";
}