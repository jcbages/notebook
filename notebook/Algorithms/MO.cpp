#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX 200005
#define SQ 450

// This is the solution for codeforces 86D
// queries in range l...r of sum of freq(x)^2 * x

struct query {
    int l, r, pos;
};

int n, q;
query queries[MAX];
int arr[MAX], freq[5*MAX];
ll tot, ans[MAX];

bool operator<(const query &q1, const query &q2) {
    int v1 = q1.l/SQ;
    int v2 = q2.l/SQ;
    if (v1 == v2) {
        return v1%2 ? q1.r > q2.r : q1.r < q2.r;
    }
    return v1 < v2;
}

#define add(pos) (tot += arr[pos]*(2LL*(freq[arr[pos]]++)+1))
#define rem(pos) (tot += arr[pos]*(-2LL*(freq[arr[pos]]--)+1))

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].pos = i;
    }
    int l = 1, r = 0;
    sort(queries, queries+q);
    for (int i = 0; i < q; ++i) {
        while (r < queries[i].r) ++r, add(r);
        while (l > queries[i].l) --l, add(l);
        while (r > queries[i].r) rem(r), r--;
        while (l < queries[i].l) rem(l), l++;
        ans[queries[i].pos] = tot;
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
    }
}