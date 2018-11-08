#include <bits/stdc++.h>
using namespace std;

// given a string A and a target B, print the occurrences of B in A
void kmp(const string &a, const string &b) {
    // build the PI function
    string s = b + "$" + a;
    int n = s.size();
    vector<int> pi(n+1);
    for (int i = 2, j; i <= n; ++i) {
        j = pi[i-1];
        while (j > 0 && s[j] != s[i-1]) {
            j = pi[j];
        }
        j += s[j] == s[i-1];
        pi[i] = j;
    }

    // print occurrences
    int m = b.size();
    for (int i = 0; i <= n; ++i) {
        if (pi[i] == m) cout << i-2*m-1 << '\n';
    }
}

int main() {
    string a = "alabalalabala";
    string b = "bala";
    
    // 3, 9 (0-based index)
    kmp(a, b);
}