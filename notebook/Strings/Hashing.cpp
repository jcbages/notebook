#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define X 137
#define MOD ((ll)1e9+7)
#define mod(n) (((n)%(MOD)+(MOD))%(MOD))

// given a string A and a target B, print the occurrences of B in A
void hashing(const string &a, const string &b) {
    // build the hash function
    string s = b + "$" + a;
    int n = s.size();
    vector<ll> h(n+1), r(n+1);
    r[0] = 1;
    for (int i = 1; i <= n; ++i) {
        h[i] = mod(h[i-1]*X+s[i-1]);
        r[i] = mod(r[i-1]*X);
    }

    // print occurrences
    int m = b.size();
    for (int i = m+1; i <= n; ++i) {
        if (mod(h[i]-mod(h[i-m]*r[m])) == h[m]) cout << i-2*m-1 << '\n';
    }
}

int main() {
    string a = "alabalalabala";
    string b = "bala";
    // 3, 9 (0-based index)
    hashing(a, b);
}
