#include<vector>
#include<queue>
using namepsace std;

#define MAX 100

using vi = vector<int>;
using vvi = vector<vi>;
vvi adjList;
int V, E;
bool visited[MAX];

int dfs(int v) { // O(V + E)
    int tam = 1;
    visited[v] = true;
    for (int w : adjList[v])
        if (!visited[w])
            tam += dfs(w);
    return tam;
}

vi dist;

void bfs(int s) { // O(V + E)
    queue<int>q;
    dist[s] = 0;
    visited[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int w : adjList[v]) 
            if (!visited[w]) {
                visited[w] = true;
                dist[w] = dist[v] + 1;
                q.push(w);
            }
    }
}

void dijkstra(int s, vi &dist) { // O((V + E) log V)
    dist.assign(adjList.size(), INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue;
        for (auto a : adjList[u]) {
            if (dist[u] + a.first < dist[a.second]) {
                dist[a.second] = dist[u] + a.first;
                pq.push({dist[a.second], a.second});
            }
        }
    }
}

int path[MAX][MAX];
int adjMat[MAX][MAX];

void floyd() { // O(V^3)
    for (int k = 0; k < V; k++) 
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++) {
                int aux = adjMat[i][k] + adjMat[k][j];
                if (aux < adjMat[i][j]) {
                    adjMat[i][j] = aux;
                    path[i][k] = k;
                }
            }
}