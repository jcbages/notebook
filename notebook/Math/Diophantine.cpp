// solve equations of the form ax + by = c
// if c%gcd(a, b) != 0 there are no solutions.
// otherwise find some solution a(xg)+b(yg)=g (g = gcd(a,b))
// using extended euclidean algorithm.

// first solution is x0 = (xg) * x/c and y0 = (yg) * c/g
// all other solutions are of the form x = x0 + k * b/g, y = y0 - k * a/g
// this is true because equality ax + by = g holds

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

void shift_solution (int & x, int & y, int a, int b, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}

// ranges are inclusive
int find_all_solutions (int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int x, y, g;
    if (! find_any_solution (a, b, c, x, y, g)) {
        return 0;
    }
    a /= g;  b /= g;

    int sign_a = a>0 ? +1 : -1;
    int sign_b = b>0 ? +1 : -1;

    shift_solution (x, y, a, b, (minx - x) / b);
    if (x < minx) {
        shift_solution (x, y, a, b, sign_b);
    }
    if (x > maxx) {
        return 0;
    }
    int lx1 = x;

    shift_solution (x, y, a, b, (maxx - x) / b);
    if (x > maxx) {
        shift_solution (x, y, a, b, -sign_b);
    }
    int rx1 = x;

    shift_solution (x, y, a, b, - (miny - y) / a);
    if (y < miny) {
        shift_solution (x, y, a, b, -sign_a);
    }
    if (y > maxy) {
        return 0;
    }
    int lx2 = x;

    shift_solution (x, y, a, b, - (maxy - y) / a);
    if (y > maxy) {
        shift_solution (x, y, a, b, sign_a);
    }
    int rx2 = x;

    if (lx2 > rx2) {
        swap (lx2, rx2);
    }
    int lx = max (lx1, lx2);
    int rx = min (rx1, rx2);

    if (lx > rx) return 0;
    return (rx - lx) / abs(b) + 1;
}

int main() {
    // find any solution for 5x+3y = 20 -- x = -20, y = 40
    int x, y, g;
    find_any_solution(5, 3, 20, x, y, g);
    cout << "x = " << x << ", y = " << y << "\n";

    // find solutions for 5x+3y = 20 in range x[-100..100], y[-200..200] -- 67
    cout << find_all_solutions(5, 3, 20, -100, 100, -200, 200) << "\n";
}