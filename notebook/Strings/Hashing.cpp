/* Given a string A and a target B, print the occurrences of B in A */
void hashing(const string &a, const string &b) {
    // Define X, MOD & mod function
    #define mod(n) (((n)%(MOD)+(MOD))%(MOD))
    const long long X = 137, MOD = 1000000007LL;

    // Build the hash function
    string s = b + "$" + a;
    int n = s.size();
    long long h[n+1], r[n+1];
    h[0] = 0, r[0] = 1;
    for (int i = 1; i <= n; ++i) {
        h[i] = mod(h[i-1]*X+s[i-1]);
        r[i] = mod(r[i-1]*X);
    }

    // Print occurrences
    int m = b.size();
    for (int i = m+1; i <= n; ++i) {
        if (mod(h[i]-mod(h[i-m]*r[m])) == h[m]) cout << i-2*m-1 << '\n';
    }
}