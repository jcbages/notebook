#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define MAXCHAR 26 // english lowercase letters

// node for english lowercase letters */
struct node {
    int f;
    vector<int> edges;
    unordered_set<int> out;
    node() {
        f = 0;
        edges.assign(MAXCHAR, -1);
    }
};
vector<node> trie;

// add root to the trie
void build() {
    trie.push_back(node());
}

// given a word, add it to the trie
void add(int index, const string &s) {
    int curr = 0;
    for (int i = 0; i < s.size(); ++i) {
        int pos = s[i]-'a';
        if (trie[curr].edges[pos] == -1) {
            trie.push_back(node());
            trie[curr].edges[pos] = trie.size()-1;
        }
        curr = trie[curr].edges[pos];
    }
    // Mark last node as string index
    trie[curr].out.insert(index);
}

// build the aho-corasick automaton
void ahocorasick() {
    queue<int> q;
    for (int i = 0; i < MAXCHAR; ++i) {
        if (trie[0].edges[i] == -1) {
            trie[0].edges[i] = 0; // root always fail to 0
        } else {
            q.push(trie[0].edges[i]);
        }
    }
    while (q.size() > 0) {
        int u = q.front(); q.pop();
        for (int i = 0; i < MAXCHAR; ++i) {
            if (trie[u].edges[i] == -1) continue;
            // perform KMP like step
            int v = trie[u].edges[i], w = trie[u].f;
            while (trie[w].edges[i] == -1) {
                w = trie[w].f;
            }
            trie[v].f = trie[w].edges[i];
            // combine occurrences
            auto out = trie[trie[v].f].out;
            for (int pos : out) {
                trie[v].out.insert(pos);
            }
            q.push(v);
        }
    }
}

// given some word, print occurrences of added patterns on it
void search(const string &s) {
    vector<pii> ans;
    for (int i = 0, curr = 0, j; i < s.size(); ++i) {
        int pos = s[i]-'a';
        // perform KMP like step
        while (trie[curr].edges[pos] == -1) {
            curr = trie[curr].f;
        }
        curr = trie[curr].edges[pos];
        auto out = trie[curr].out;
        for (int pos : out) {
            ans.push_back({i, pos});
        }
    }

    // print answrs
    for (int i = 0; i < ans.size(); ++i) {
        cout << "{" << ans[i].first << ", " << ans[i].second << "}\n";
    }
}

int main() {
    // build the trie
    build();

    // add some patterns to the trie
    string patterns[] = {"alabala", "bala", "ilibili"};
    for (int i = 0; i < 3; ++i) {
        add(i, patterns[i]);
    }

    // build the aho-corasick automaton
    ahocorasick();

    // search for occs of pattern in given word -- {25, 1}, {25, 0}, {60, 2}
    search("thisisatestwordwithalabalabutnotonlythatalsoalabaandilibili");
}