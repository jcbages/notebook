/* Comparison function + vector for suffix array */
vector<long long> rank2;
bool cmp(const int i, const int j) {return rank2[i] < rank2[j];}

/* Calculate the suffix array for the given word */
vector<int> suffix_array(const string &s) {
    int n = s.size();
    vector<int> sa(n), rank(n);
    rank2.resize(n); 
    // Initialize for iter 1
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank[i] = s[i];
    }
    // Calculate for subsequent iters
    for (int len = 1; len < n; len *= 2) {
        for (int i = 0; i < n; i++) {
            rank2[i] = ((long long) rank[i]<<32)+((i+len < n) ? rank[i+len] : -1);
        }
        sort(sa.begin(), sa.end(), cmp);
        for (int i = 0; i < n; i++) {
            if (i > 0 && rank2[sa[i]] == rank2[sa[i-1]]) {
                rank[sa[i]] = rank[sa[i-1]];
            } else {
                rank[sa[i]] = i;
            }
        }
    }
    return sa;
}

/* Calculate the LCP array for the given word */
vector<int> lcp_array(const vector<int> &sa, const string &s) {
    int n = s.size();
    vector<int> rank(n);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    vector<int> ans(n);
    for (int i = 0, l = 0; i < n; i++) {
        if (rank[i] > 0) {
            int j = sa[rank[i]-1];
            while (s[i+l] == s[j+l]) l++;
            ans[rank[i]] = l > 0 ? l-- : l;
        }
    }
    return ans;
}