using namespace std;

#define MAX_V 100 

int hora; int horaVertice[MAX_V]; int alcanzable[MAX_V];
int hijosRaiz;

void dfs(int u, int uParent) {
    horaVertice[u] = alcanzable[u] = hora; hora++;
    for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    if (v == uParent) continue;
    if (horaVertice[v] == 0) {
    if (uParent == 0) hijosRaiz++;
    dfs(v, u);
    if (alcanzable[v] >= horaVertice[u])
    if (uParent != 0) {
    // u es punto de articulaci´on.
    }
    alcanzable[u] = min(alcanzable[u], alcanzable[v]);
    } else
    alcanzable[u] = min(alcanzable[u], horaVertice[v]);
    }
}

int main() {
    hora = 1;
    memset(horaVertice, 0, n*sizeof(horaVertice[0]));
    memset(alcanzable, -1, n*sizeof(alcanzable[0]));

    for (int i = 1; i <= n; ++i) {
        if (!horaVertice[i]) {
            hijosRaiz = 0;
            dfs(i, 0);
            if (hijosRaiz > 0) {
                // La raiz es un punto de articulacion
            }
        }
    }
    
    return 0;
}