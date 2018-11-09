// impartial games are equivalent to Nim.
// a game is impartial iff the only difference between 
// the players is the order in which they take turns.

// each composite game can be divided into independent 
// subgames (like each Nim-pile is an independent game).

// the XOR of a composite game determines the winner of 
// the game when both parts play optimally.
//  * if XOR = 0, player 1 will lose
//  * otherwise, player 1 will win

// grundy number of some state is the mex of the grundy 
// numbers of reachable states from that state.

// mex is the smallest non-negative number not present in a set.
// example: mex(0, 1, 2) = 3, mex(1, 2, 3) = 0, mex(0, 2) = 1

// this is the solution for the problem split game (cf gym)

#include <bits/stdc++.h>
using namespace std;
#define MAX 2001

vector<int> dp;

int grundy(int n) {
    assert(n > 0);
    if (n == 1) {
        return dp[n] = 0;
    } else if (dp[n] != -1) {
        return dp[n];
    } else {
        set<int> mex;
        for (int x = 1; x < n; ++x) {
            int q = n/x, r = n%x;
            if (q%2 == 0) {
                if (r > 0) {
                    mex.insert(grundy(r));
                } else {
                    mex.insert(0);
                }
            } else {
                if (r > 0) {
                    mex.insert(grundy(r)^grundy(x));
                } else {
                    mex.insert(grundy(x));
                }
            }
        }
        int ans = 0;
        while (mex.find(ans) != mex.end()) {
            ++ans;
        }
        return dp[n] = ans;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, ans = 0;
    cin >> n;
    dp.assign(MAX, -1);
    for (int i = 0, v; i < n; ++i) {
        cin >> v;
        ans ^= grundy(v);
    }
    cout << (ans == 0 ? "Second\n" : "First\n");
}