#include <bits/stdc++.h>
using namespace std;

// O(n) sieve for all primes
vector<int> linear_sieve(int n) {
    vector<int> primes;
    vector<bool> is_composite(n, false);
    for (int i = 2; i < n; ++i) {
        // no composite, so must be prime
        if (!is_composite[i]) {
            primes.push_back(i);
        }
        // all smallest primes will be multiplied by every i 
        for (int j = 0; j < primes.size() && primes[j]*i < n; ++j) {
            is_composite[i*primes[j]] = true; // can be writter as i*p
            // future primes wont be smallest, break
            if (i%primes[j] == 0) {
                break;
            }
        }
    }
    return primes;
}

int main() {
    // get all primes between up to 100 (exclusive)
    vector<int> primes = linear_sieve(100);

    // 2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97
    for (int prime : primes) {
        cout << prime << " ";
    }
    cout << "\n";
}