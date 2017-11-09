/* Node for english lowercase letters */
struct node {
    int edges[26];
    bool is_end;
    node() {
        is_end = false;
        memset(edges, 255, sizeof(edges));
    }
};
vector<node> trie;

/* Given a word, add it to the trie */
void add(int curr, const string &s) {
    // Traverse the trie & add nodes when necessary
    for (int i = 0; i < s.size(); ++i) {
        if (trie[curr].edges[s[i]-'a'] == -1) {
            trie[curr].edges[s[i]-'a'] = trie.size();
            trie.push_back(node());
        }
        curr = trie[curr].edges[s[i]-'a'];
    }
    // Mark last node as an end
    trie[curr].is_end = true;
}

/* Given a word, check if it exist in the trie */
bool exist(int curr, const string &s) {
    // Try to traverse the trie or return if node doesnt exist
    for (int i = 0; i < s.size(); ++i) {
        if (trie[curr].edges[s[i]-'a'] == -1) {
            return false;
        }
        curr = trie[curr].edges[s[i]-'a'];
    }
    // String exist if it's an end & not a preffix
    return trie[curr].is_end;
}

/* Initialize the trie with the root node */
void init() {trie.push_back(node());}