#include<iostream>
#include<queue>
#include<vector>
using namespace std;

#define INF 1e5
#define V 10000
#define A 10000000

using vi = vector<int>;
using vvi = vector<vi>;

vvi adj;
bool visited[V];
int parent[V];
int cap[V][V];

void bfs(int s, int t) {
    queue<int> q;
    memset(visited, 0, sizeof(visited));
    q.push(s);
    parent[s] = -1; visited[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == t) break;
        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (!visited[v] && (cap[u][v] > 0)) {
                parent[v] = u;
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int sendFlow(int s, int t) {
    // Intentamos llegar de s a t
    bfs(s, t);
    if (!visited[t])
        return 0; // No pudimos
    // Buscamos capacidad m´as peque˜na en el camino
    int flow = INF, v = t;
    while (v != s) {
        flow = min(cap[parent[v]][v], flow);
        v = parent[v];
    }
    // Mandamos flujo
    v = t;
        while (v != s) {
        cap[parent[v]][v] -= flow;
        cap[v][parent[v]] += flow; // INVERSA
        v = parent[v];
    }
    return flow;
}

int edmondsKarp(int s, int t) {
    int ret = 0, flow = 0;
    do {
        flow = sendFlow(s, t);
        ret += flow;
    } while (flow > 0);
    return ret;
}

int main() {
    return 0;
}