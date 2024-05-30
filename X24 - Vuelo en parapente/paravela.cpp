/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */
  
/*
  Indica el nombre y apellidos de los componentes del grupo
  ---------------------------------------------------------
  Componente 1: ALEX GUILLERMO BONILLA TACO
  Componente 2: 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <queue>
#include <stack>

using namespace std;


//coste de O(2n), es decir, O(n), lineal, siendo n el numero de elementos de entrada que se procesan por cola. las demas operaciones son de tiempo constante O(1)
bool tratar_caso() {
  // Implementa el código para tratar un caso de prueba.
    int n;
  // Esta función debe devolver `false` si, en lugar de un caso de prueba,
  // se ha encontrado con la marca de fin de entrada (-1).
    cin >> n;
    if (n == -1)
        return false;
    stack<int> pila;
    queue<int> cola;

    while (n != -1)//O(n)
    {
        cola.push(n);//O(1)
        cin >> n;
    }
    while (!cola.empty())//O(n)
    {
        n = cola.front();//O(1)
        if (pila.empty())//O(1)
        {
            cout << "NO HAY\n";
            pila.push(n);//O(1)
            cola.pop();//O(1)
        }
        else if (pila.top() > n)
        {
            cout << pila.top() << endl;
            ;
            pila.push(n);//O(1)
            cola.pop();//O(1)
        }
        else if (pila.top() <= n)//O(1)
        {
            while (!pila.empty() && pila.top() <= n)//O(1)
            {
                pila.pop();//O(1)
            }
        }
    }
    cout<<"---\n";
    // En caso contrario, debe procesar el caso de prueba y devolver `true`.
    return true;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
