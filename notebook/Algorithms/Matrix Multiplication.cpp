#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vii;

// multiply two matrices (n1xm) x (mxn2) resulting in (nxn) matrix
vii multiply(vii &A, vii &B) {
    int N1 = A.size();
    int N2 = B[0].size();
    int M = A[0].size();

    vii C(N1, vi(N2));
    for (int i = 0; i < N1; ++i) {
        for (int j = 0; j < N2; ++j) {
            for (int k = 0; k < M; ++k) {
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    return C;
}

// get identity matrix of size NxN
vii get_identity(int N) {
    vii C(N, vi(N));
    for (int i = 0; i < N; ++i) {
        C[i][i] = 1;
    }
    return C;
}

// fast matrix exponentiation (matrices must be square) A^x
vii fast_pow(vii A, int x) {
    int N = A.size();
    vii C = get_identity(N);
    while (x > 0) {
        if (x&1) {
            C = multiply(C, A);
        }
        A = multiply(A, A);
        x /= 2;
    }
    return C;
}

int main() {
    // init fib recurrence matrix
    // | 1 1 |
    // | 1 0 |
    vii A(2, vi(2));
    A[0][0] = A[0][1] = A[1][0] = 1;

    // init fib vector
    // | 1 | f(2)
    // | 1 | f(1)
    vii B(2, vi(1));
    B[0][0] = B[1][0] = 1;

    // do fast exponentiation -- f(10) = 34+21
    // | 34 21 |
    // | 21 13 | 
    vii C = fast_pow(A, 10-2); // fib(10) = 10-initial_n (2)
    print_mat(C);

    // get result multiplying by vector --
    // | 55 |
    // | 34 |
    vii res = multiply(C, B);
    cout << res[0][0] << "\n";
}