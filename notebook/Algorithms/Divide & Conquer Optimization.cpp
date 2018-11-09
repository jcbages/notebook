// solution for problem guardians of the lunatic IOI 14

#include <stdio.h>
#define ll long long
#define infinity 1111111111111111111ll

ll C[8111];
ll sums[8111];
ll F[811][8111];
int P[811][8111];

ll cost(int i, int j) {
    return i > j ? 0 : (sums[j] - sums[i-1]) * (j - i + 1);
}

void fill(int g, int l1, int l2, int p1, int p2) {
    // fill(g,l1,l2,p1,p2) calculates all P[g][l] and F[g][l] for l1 <= l <= l2,
    // with the knowledge that p1 <= P[g][l] <= p2

    // if l1 > l2, then there's nothing to calculate
    if (l1 > l2) return;

    int lm = l1 + l2 >> 1;
    // calculate P[g][lm] and F[g][lm]
    P[g][lm] = -1;
    F[g][lm] = infinity;
    for (int k = p1; k <= p2; k++) {
        ll new_cost = F[g-1][k] + cost(k+1,lm);
        if (F[g][lm] > new_cost) {
            F[g][lm] = new_cost;
            P[g][lm] = k;
        }
    }

    // calculate both sides of lm
    fill(g, l1, lm-1, p1, P[g][lm]);
    fill(g, lm+1, l2, P[g][lm], p2);
}

int main() {
    int G, L;
    scanf("%d%d", &L, &G);
    sums[0] = 0;
    for (int i = 1; i <= L; i++) {
        scanf("%lld", C + i);
        sums[i] = sums[i-1] + C[i];
    }
    #define cost(i,j) (sums[j]-sums[(i)-1])*((j)-(i)+1)

    for (int l = 0; l <= L; l++) {
        F[1][l] = cost(1,l);
        P[1][l] = 0;
    }

    for (int g = 2; g <= G; g++) {
        fill(g, 0, L, 0, L);
    }    
    printf("%lld\n", F[G][L]);
}