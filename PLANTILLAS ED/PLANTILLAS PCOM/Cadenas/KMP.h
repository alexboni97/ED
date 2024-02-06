#include<vector>
using namespace std;

string T, P;
vector<int>b; // back table
int n, m;

/* Otra aplicacion del KMP:
Dada una cadena, encontrar la longitud minima de una subcadena que se repite N veces
para formar la cadena.

- Si alguna cadena se repite, su longitud debe ser: l = cadena.size() - b[b.size() - 1]
- Si (cadena.size() % l == 0) es la cadena que queremos
- Else la longitud minima es la longitud de la cadena
*/
// O(pattern size) === O(m)
void kmpPreprocess() { // before calling kmpSearch
    int i = 0, j = -1; b[0] = -1;
    while (i < m) {
        while (j >= 0 && P[i] != P[j]) j = b[j];
        ++i; ++j;
        b[i] = j;
    }
}

// (O(text size) === O(n)) + O(m)
void kmpSearch() {
    int i = 0, j = 0;
    while (i < n) {
        while (j >= 0 && T[i] != P[j]) 
            j = b[j]; // different reset j using b
        ++i; ++j;
        if (j == m) {
            printf("P si found at index %d in T\n", i - j);
            j = b[j];
        }
    }
}