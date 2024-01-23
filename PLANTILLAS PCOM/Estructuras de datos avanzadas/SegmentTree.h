#include<vector>
using namespace std;

class SegmentTree {
private:
    vector<int>st;
    int tam;
    int query(int vertex, int L, int R, int i, int j) {
        if (i > R || j < L) return 0;
        if (L >= i && R <= j) return st[vertex];
        int mitad = (L + R) / 2;
        return query(vertex * 2, L, mitad, i, j) + query(vertex * 2 + 1, mitad + 1, R, i, j);
    }
    void update(int vertex, int l, int r, int pos, int newVal) {
        if (pos < l || r < pos) return;
        if (l == r) {
            st[vertex] = newVal;
            return;
        }
        int m = (l + r) / 2;
        if (l <= pos && pos <= m)
            update(vertex * 2, l, m, pos, newVal);
        else
            update(vertex * 2 + 1, m + 1, r, pos, newVal);
        st[vertex] = st[vertex * 2] + st[vertex * 2 + 1];
    }
    void build(int *values, int p, int l, int r) {
        if (l == r) {
            st[p] = values[l];
            return;
        }
        int m = (l + r) / 2;
        build(values, 2 * p, l, m);
        build(values, 2 * p + 1, m + 1, r);
        st[p] = st[p * 2] + st[p * 2 + 1];
    }
public:
    SegmentTree(int maxN) {
        st.reserve(4 * maxN + 10);
    }
    int query(int a, int b) {
        return query(1, 0, tam - 1, a, b);
    }
    void update(int pos, int newVal) {
        update(1, 0, tam - 1, pos, newVal);
    }
    void build(int *values, int n) {
        tam = n;
        build(values, 1, 0, n - 1);
    }
};