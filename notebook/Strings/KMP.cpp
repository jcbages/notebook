/* Given a string A and a target B, print the occurrences of B in A */
void kmp(const string &a, const string &b) {
    // Build the PI function
    string s = b + "$" + a;
    int n = s.size(), pi[n+1];
    pi[0] = pi[1] = 0;
    for (int i = 2, j; i <= n; ++i) {
        j = pi[i-1];
        while (j > 0 && s[j] != s[i-1]) j = pi[j];
        if (s[j] == s[i-1]) j++;
        pi[i] = j;
    }

    // Print occurrences
    int m = b.size();
    for (int i = 0; i <= n; ++i) {
        if (pi[i] == m) cout << i-2*m-1 << '\n';
    }
}