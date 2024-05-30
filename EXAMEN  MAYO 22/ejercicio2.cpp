//-------------------------------------------------------
// Ejercicio 2: Nodos intermedios. Mayo 2022
// Escribe tu nombre y respuestas en las zonas indicadas
//-------------------------------------------------------
//@ <answer>
// Nombre :
// Usiario del Juez de Clase :
// Usuario del Juez de Exámenes :
//@ </answer>

#include <iostream>
#include <fstream>
#include "Arbin_Smart.h"

//Añade las librerías que necesites
//@ <answer>


//@ </answer>

using namespace std;

//-------------------------------------------------------
//Escribe la solución. Puedes definir las funciones auxiliares
// y tipos de datos que necesites.
//@ <answer>


int nodos_intermedio(const BinTree<int>& arbol) {

}

//@ </answer>
//
// ¡No modifiques nada debajo de esta línea!
// ----------------------------------------------------------------
void resuelveCaso() {
    BinTree<int> arbol = read_tree<int>(cin);
    cout << nodos_intermedio(arbol) << endl;
}


int main() {
#ifndef DOMJUDGE
    ifstream in("sample2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int num_casos;
    cin >> num_casos;
    for (int i = 0; i < num_casos; i++) {
        resuelveCaso();
    }
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;

} // main