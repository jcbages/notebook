/* Node for english lowercase letters */
struct node {
    int edges[26], f;
    unordered_set<int> out;
    node() {
        f = 0;
        memset(edges, 255, sizeof(edges));
    }
};
vector<node> trie;

/* Given a word, add it to the trie */
void add(int curr, int pos, const string &s) {
    // Traverse the trie & add nodes when necessary
    for (int i = 0; i < s.size(); ++i) {
        if (trie[curr].edges[s[i]-'a'] == -1) {
            trie[curr].edges[s[i]-'a'] = trie.size();
            trie.push_back(node());
        }
        curr = trie[curr].edges[s[i]-'a'];
    }
    // Mark last node as string index
    trie[curr].out.insert(pos);
}

/* Build the aho-corasick automaton */
void ahocorasick() {
    queue<int> q;
    for (int i = 0; i < 26; ++i) {
        if (trie[0].edges[i] == -1) {
            trie[0].edges[i] = 0; // always fail to 0
        } else {
            q.push(trie[0].edges[i]);
        }
    }
    int u, v, w, s;
    unordered_set<int> out;
    unordered_set<int>::iterator it;
    while (q.size() > 0) {
        u = q.front(), q.pop();
        for (int i = 0; i < 26; ++i) {
            if (trie[u].edges[i] == -1) continue;
            // Perform KMP step like here
            v = trie[u].edges[i], w = trie[u].f;
            while (trie[w].edges[i] == -1) w = trie[w].f;
            trie[v].f = trie[w].edges[i];
            // Combine occurrences
            out = trie[trie[v].f].out;
            for (it = out.begin(); it != out.end(); ++it) {
                trie[v].out.insert(*it);
            }
            q.push(v);
        }
    }
}

/* Given a word, print occurrences of added patterns on it */
void search(const string &s) {
    vector<pair<int, int> > ans;
    unordered_set<int> out;
    unordered_set<int>::iterator it;
    for (int i = 0, curr = 0, j; i < s.size(); ++i) {
        while (trie[curr].edges[s[i]-'a'] == -1) {
            curr = trie[curr].f;
        }
        curr = trie[curr].edges[s[i]-'a'];
        out = trie[curr].out;
        for (it = out.begin(); it != out.end(); ++it) {
            ans.push_back(make_pair(i, *it));
        }
    }
    for (int i = 0; i < ans.size(); ++i) {
        cout << "{" << ans[i].first << ", ";
        cout << ans[i].second << "}" << '\n';
    }
}

/* Initialize the trie with the root node */
void init() {trie.push_back(node());}