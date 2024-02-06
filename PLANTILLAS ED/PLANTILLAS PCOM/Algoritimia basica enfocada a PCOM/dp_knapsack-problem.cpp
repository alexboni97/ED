#include<iostream>
#include<cstring>
using namespace std;

#define NMAX 50
#define MMAX 20

int weights[NMAX]; int values[NMAX]; // 0-based
int n; int M;
int value; bool cuales[NMAX];
int dp[NMAX + 1][MMAX + 1];

void knapsack() {
    memset(dp, 0, (M+1)*sizeof(dp[0][0]));
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = 0;
        for (int j = 1; j <= M; ++j) {
            if (weights[i-1] > j)
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - weights[i-1]] + values[i-1]);
        }
    }
    value = dp[n][M];

    // objects calculation
    int remainder = M;
    for (int i = n; i >= 1; --i) {
        if (dp[i][remainder] == dp[i - 1][remainder]) {
            // object i not taken
            cuales[i] = false;
        } else { // object i taken
            cuales[i] = true;
            remainder = remainder - weights[i - 1];
        }
    }
}


int main() {

    knapsack();

    return 0;
}