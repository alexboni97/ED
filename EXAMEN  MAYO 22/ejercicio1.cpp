//-------------------------------------------------------
// Ejercicio 1: Listas equilibradas. Mayo 2022
// Escribe tu nombre y respuestas en las zonas indicadas
//-------------------------------------------------------
//@ <answer>
// Nombre :
// Usiario del Juez de Clase :
// Usuario del Juez de Exámenes :
//@ </answer>

#include <iostream>
#include <fstream>
#include <string>
#include <list>
//Añade las librerías que necesites:
//@ <answer>
//@ </answer>


using namespace std;


//-------------------------------------------------------
//Rellena adecuadamente la función y RAZONA el coste
//@ <answer>

void reconstruir(list<int>& lista) {

}


//@ </answer>
//
// ¡No modifiques nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    int n;
    list<int> lista;
    cin >> n;
    if (!cin)
        return false;

    for (int i = 0; i < n; i++) {
        int elem;
        cin >> elem;
        lista.push_back(elem);
    }

    reconstruir(lista);

    bool primero = true;
    for (int x : lista) {
        if (primero) {
            primero = false;
            cout << x;
        }
        else {
            cout << " " << x;
        }
    }
    cout << endl;

    return true;
}

int main() {

#ifndef DOMJUDGE
    ifstream in("sample1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso())
        ;

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;

} // main