#include<iostream>
#include<cstring>
using namespace std;

#define MAX 100

// CNA == Combinatorial Numbers Accumulated
int CNA[MAX + 1][MAX + 1];
int CNA_AUX[MAX + 1];

int pascal(int n, int r) {
    memset(CNA, 0, (r+1) * sizeof(CNA[0][0]));
    CNA[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        CNA[i][0] = 1;
        for (int j = 1; j <= r; j++) {
            CNA[i][j] = CNA[i - 1][j - 1] + CNA[i - 1][j];
        }
    }
    return CNA[n][r];
}

int pascal2(int n, int r) {
    memset(CNA_AUX, 0, (r+1) * sizeof(CNA_AUX[0]));
    CNA_AUX[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= r; j++) {
            CNA_AUX[j] = CNA_AUX[j - 1] + CNA_AUX[j];
        }
    }
    return CNA_AUX[r];
}

int main() {
    memset(CNA, -1, sizeof(CNA));
    cout << pascal(5, 3) << "\n";
    // Same with less space
    // cout << pascal2(5, 3) << "\n";
    return 0;
}