#include <bits/stdc++.h>
using namespace std;

// Function f is multiplicative if:
// For every pair of co-prime integers p, q (gcd(p, q) = 1), then f(p*q) = f(p)*f(q)
// Unless for all n, f(n) = 0. We know that f(1) must be 1 as f(n) = f(n)*f(1)
// f(n) & g(n) are identical iff for every prime p and number k >= 0 then f(p^k) = g(p^k)
// So we only need to know about f(p^k)

// Example of linear sieve for calculating phi(n) multiplicative function (euler totient) 
vector<int> euler_totient(int n) {
    vector<int> primes, phi(n);
    vector<bool> is_composite(n, false);
    for (int i = 2; i < n; ++i) {
        if (!is_composite[i]) {
            // i is prime, so get f(i) manually, for totient is i-1
            primes.push_back(i);
            phi[i] = i-1;
        }
        for (int j = 0; j < primes.size() && i*primes[j] < n; ++j) {
            if (i%primes[j] == 0) {
                // i and primes[j] are NOT co-prime, we need to find a relation
                // in the case of euler totient, phi(i*primes[j]) = primes[h]*phi(i)
                phi[i*primes[j]] = phi[i]*primes[j];
                break; // break as further primes wont be smallest
            } else {
                // i and primes[j] are co-prime, so f(i*primes[j]) = f(i)*f(primes[j])
                phi[i*primes[j]] = phi[i]*phi[primes[j]];
            }
        }
    }
    phi[1] = 1;
    return phi;
}

int main() {
    // get number of co-primes for all numbers up to 20 (exclusive)
    vector<int> phi = euler_totient(20);

    // 0 1 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
    for (int num_coprimes : phi) {
        cout << num_coprimes << " ";
    }
    cout << "\n";
}