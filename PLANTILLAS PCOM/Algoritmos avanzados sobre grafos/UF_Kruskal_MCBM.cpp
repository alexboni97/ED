#include<vector>
#include<algorithm>
using namespace std;

struct UFDS {
    vector<int> p;
    int numSets;
    UFDS(int n) : p(n, 0), numSets(n) {
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int find(int x) {
        return (p[x] == x) ? x : p[x] = find(p[x]);
    }
    void merge(int x, int y) {
        int i = find(x), j = find(y);
        if (i == j) return;
        p[i] = j;
        --numSets;
    }
};

using arista = pair<int, pair<int,int>>; // <coste, extremos>

vector<arista>aristas;
// guardar aristas
sort(aristas.begin(), aristas.end());

UFDS uf(V);
int coste = 0;
for (auto ar : aristas) {
    if (uf.find(ar.second.first) != uf.find(ar.second.second)) {
        uf.merge(ar.second.first, ar.second.second);
        coste += ar.first;
        if (uf.numSets == 1) break;
    }
}
cout << coste << "\n";


int M, N; // M parte izq, N parte der
vector<vector<int>>grafo;
vector<int>match, vis;


int aug(int l) {
    // devuelve 1 si encuentra un augmenting path para el matching M representado en match
    if (vis[l]) return 0;
    vis[l] = 1;
    for (auto r : grafo[l]) {
        if (match[r] == -1 || aug(match[r])) {
            match[r] = l;
            return 1;
        }
    }
    return 0;
}


int merge_mcbm() {
    int mcbm = 0;
    match.assign(N + M, -1);
    for (int l = 0; l < M; l++) {
        vis.assign(M, 0);
        mcbm += aug(l);
    }
    return mcbm;
}

