/* Given a string A and a target B, print the occurrences of B in A */
void zfunc(const string &a, const string &b) {
    // Build the Z function
    string s = b + "$" + a;
    int n = s.size(), z[n];
    z[0] = 0;
    for (int i = 1, l = 0, r = 0, k; i < n; ++i) {
        if (i > r) {
            l = r = i;
            while (r < n && s[r-l] == s[r]) ++r;
            z[i] = r-l, --r;
        } else {
            k = i-l;
            if (z[k] < r-i+1) {
                z[i] = z[k];
            } else {
                l = i;
                while (r < n && s[r-l] == s[r]) ++r;
                z[i] = r-l, --r;
            }
        }
    }

    // Print occurrences
    int m = b.size();
    for (int i = 0; i < n; ++i) {
        if (z[i] == m) cout << i-m-1 << '\n';
    }
}