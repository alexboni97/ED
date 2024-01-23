#include<iostream>
#include<cstring>
using namespace std;

#define MAX 100

// CNA == Combinatorial Numbers Accumulated
int CNA[MAX + 1][MAX + 1];

int combination(int n, int r) {
    if (r == 0 || r == n) return 1;
    if (CNA[n][r] != -1) return CNA[n][r];
    return CNA[n][r] = combination(n - 1, r - 1) + combination(n - 1, r);
}

int main() {
    memset(CNA, -1, sizeof(CNA));
    cout << combination(5, 3) << "\n";
    return 0;
}