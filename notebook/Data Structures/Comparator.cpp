struct CustomCompare {
    bool operator()(const int &v1, const int &v2) {
        return v1 > v2; // smaller to bigger (reverse)
    }
};
// pq with custom comparator
priority_queue<int, vector<int>, CustomCompare> pq;
// pq from smaller to bigger
priority_queue<int, vector<int>, greater<int> > q;
