#include <bits/stdc++.h>
using namespace std;
#define inf ((int)1e9)
#define SIZE 9
#define SEGTREE (((int)log2(SIZE))+2)

// segment tree for RMQ
vector<int> segtree(1<<SEGTREE);

// query the min in range [a...b]
int query(int i, int l, int r, int a, int b) {
    if (b < l || a > r) {
        return inf;
    } else if (a <= l && r <= b) {
        return segtree[i];
    } else {
        int mid = (l+r)/2;
        int v1 = query(2*i, l, mid, a, b);
        int v2 = query(2*i+1, mid+1, r, a, b);
        return min(v1, v2);
    }
}

int query(int l, int r) {
    return query(1, 1, SIZE, l, r);
}

// set item in position p to have value v
void update(int i, int l, int r, int p, int v) {
    if (l == r) {
        segtree[i] = v;
    } else {
        int mid = (l+r)/2;
        if (p <= mid) {
            update(2*i, l, mid, p, v);
        } else {
            update(2*i+1, mid+1, r, p, v);
        }
        segtree[i] = min(segtree[2*i], segtree[2*i+1]);
    }
}

void update(int p, int v) {
    update(1, 1, SIZE, p, v);
}

int main() {
    int arr[] = {6, 1, 6, 200, 195, 1, 6, 1, 90};
    
    // build initial segtree
    for (int i = 1; i <= SIZE; ++i) {
        update(i, arr[i-1]);
    }

    // query some ranges in segtree -- 1, 195, 6
    cout << query(1, 9) << "\n";
    cout << query(4, 5) << "\n";
    cout << query(7, 7) << "\n";
}