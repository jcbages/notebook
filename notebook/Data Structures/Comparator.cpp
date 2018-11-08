struct CustomCompare {
    bool operator()(const int &v1, const int &v2) {
        return items_rank[v1] > items_rank[v2];
    }
};

// pq with custom comparator
priority_queue<int, vector<int>, CustomCompare> pq;

// pq from smaller to bigger
priority_queue<int, vector<int>, greater<int> > q;