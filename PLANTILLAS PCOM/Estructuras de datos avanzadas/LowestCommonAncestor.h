#include<vector>
#include"SegmentTree.h"
using namespace std;
#define MAX_V 100

using vi = vector<int>;

vi adj[MAX_V];

int idx;
int euler[2 * MAX_V - 1];
int prof[2 * MAX_V - 1];
int first[MAX_V];


void eulerTour(int u, int parent, int d) {

    first[u] = idx; euler[idx] = u; prof[idx] = d; idx++;

    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v == parent) continue;

        eulerTour(v, u, d + 1);
        euler[idx] = u; prof[idx] = d; idx++;
    }
}

int lca(int u, int v) {
    SegmentTree st(MAX_V);
    return euler[st.query(first[u], first[v])];
}