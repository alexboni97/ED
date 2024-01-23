using namespace std;

#define MAX_V 100

int hora; int horaVertice[MAX_V]; int alcanzable[MAX_V];
void dfs(int u, int uParent) {
horaVertice[u] = alcanzable[u] = hora; hora++;
for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    if (v == uParent) continue; // B.E. con el padre, que ignoramos
    if (horaVertice[v] == 0) { // No visitado
        dfs(v, u);
        if (alcanzable[v] > horaVertice[u]) {
        // La arista u-v es un puente
    }
    alcanzable[u] = min(alcanzable[u], alcanzable[v]);
    } 
    else
        alcanzable[u] = min(alcanzable[u], horaVertice[v]); // BACK EDGE
    }
}

int main() {
    hora = 1;
    memset(horaVertice, 0, n*sizeof(horaVertice[0]));

    for (int i = 1; i <= n; ++i) {
        if (!horaVertice[i])
            dfs(i, 0);
    }
    return 0;
}