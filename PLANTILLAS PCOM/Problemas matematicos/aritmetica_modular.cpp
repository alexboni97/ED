#include<iostream>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
int lcm(int a, int b) {
    return a * (b / gcd(a, b));
}

int extendedEuclidRec(int a, int b, int &u, int &v) {
    if (!b) {
        u = 1;
        v = 0;
        return a;
    }
    int r = extendedEuclidRec(b, a % b, u, v);
    int uAux = v;
    int vAux = u - (a / b) * v;
    u = uAux;
    v = vAux;
    return r;
} // extendedEuclidRec

typedef pair<unsigned int, unsigned int> uu;
// <µ,λ> : <inicio ciclo, longitud ciclo>
// f es la funcion que pide el enunciado
uu floydCycleFinding(unsigned int x0) {
    int tortoise = f(x0), hare = f(f(x0));
    while (tortoise != hare) {
    tortoise = f(tortoise); hare = f(f(hare));
    }
    int mu = 0; hare = x0;
    while (tortoise != hare) {
    tortoise = f(tortoise); hare = f(hare); mu++;
    }
    int lambda = 1; hare = f(tortoise);
    while (tortoise != hare) {
    hare = f(hare); lambda++;
    }
    return uu(mu, lambda);
}