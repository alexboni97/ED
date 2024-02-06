#include<iostream>
using namespace std;

#define MAXLONG 1000
int dp[MAXLONG][MAXLONG];
string ducks; // 0-based

int shootin_palindrome(int i, int j) { // ducks[i..j]
    int & res = dp[i][j];
    if (res == -1) {
    if (i > j) res = 0;
    else if (i == j) res = 1;
    else if (ducks[i] == ducks[j])
        res = 2 + shootin_palindrome(i + 1, j - 1);
    else
        res = max(shootin_palindrome(i + 1, j), shootin_palindrome(i, j - 1));
    }
    return res;
}

void print(int i, int j) {
    if (i > j) return;
    if (i == j) cout << ducks[i];
    else if (ducks[i] == ducks[j]) {
        cout << ducks[i];
        print(i + 1, j - 1);
        cout << ducks[j];
    } 
    else if (dp[i][j] == dp[i + 1][j])
        print(i + 1, j);
    else
        print(i, j - 1);
}

bool caseResolution() {
    cin >> ducks;
    if (!cin) return false;

    int N = ducks.length();
    for (int i = 0; i < N; ++i)
        for (int j = i; j < N; ++j)
            dp[i][j] = -1;
    
    shootin_palindrome(0, N - 1);
    print(0, N - 1); 
    cout << '\n';
    return true;
}


int main() {
    while (caseResolution());
    return 0;
}