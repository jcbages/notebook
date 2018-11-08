#include <bits/stdc++.h>
using namespace std;
#define MAXCHAR 26 // english lowercase letters

struct node {
    bool is_end;
    vector<int> edges;
    node() {
        is_end = false;
        edges.assign(MAXCHAR, -1);
    }
};
vector<node> trie;

// add root to the trie
void build() {
    trie.push_back(node());
}

// given some word s, add it to the trie
void add(const string &s) {
    int curr = 0;
    for (int i = 0; i < s.size(); ++i) {
        int pos = s[i]-'a';
        if (trie[curr].edges[pos] == -1) {
            trie.push_back(node());
            trie[curr].edges[pos] = trie.size()-1;
        }
        curr = trie[curr].edges[pos];
    }
    // mark last node as an end
    trie[curr].is_end = true;
}

// given some word, check if it exist in the trie
bool exist(const string &s) {
    int curr = 0;
    for (int i = 0; i < s.size(); ++i) {
        int pos = s[i]-'a';
        if (trie[curr].edges[pos] == -1) {
            return false;
        }
        curr = trie[curr].edges[pos];
    }
    // string exist if it's an end (not only a preffix)
    return trie[curr].is_end;
}

int main() {
    // build the trie
    build();

    // add some words to the trie
    add("alabalafirstword");
    add("alabalasecondword");
    add("thirdword");

    // query for some words existence -- true, false, false
    cout << exist("alabalasecondword") << "\n";
    cout << exist("thirdwor") << "\n";
    cout << exist("notexistingword") << "\n";
}