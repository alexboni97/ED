using namespace std;

#define TOCADO 0
#define HUNDIDO 1
#define NO_VISTO 2

using vi = vector<int>;
using vvi = vector<vi>;

vvi adj;

bool dfs(int u) {
    estado[u] = TOCADO;
    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (estado[v] == TOCADO)
        return true;
        else if ((estado[v] == NO_VISTO) && dfs(v))
        return true;
    }
    estado[u] = HUNDIDO;
    return false;
}