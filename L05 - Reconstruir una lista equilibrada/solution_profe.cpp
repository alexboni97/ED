/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*
  Solución al problema de Reconstruir Lista Equilibrada
  
  Manuel Montenegro
*/

 
// Añade los #include que necesites
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <list>

#include <stack>  


using namespace std;



// COSTE:
// ------
// Tenemos un bucle al principio que recorre todas las posiciones de
// la lista de entrada. En cada iteración todas las operaciones tienen
// coste O(1). El coste de ese bucle es O(N), donde N es la longitud
// de la lista. Luego hay otro bucle que, en el caso peor, hace tantas
// iteraciones como números positivos hay en la entrada, por lo que
// también tiene coste O(N) en el caso peor.
//
// Por tanto, el coste del algoritmo es O(N), donde N es la longitud
// de la lista de entrada.

void reconstruir(list<int> &lista) {
  // Similar al problema de 'Paréntesis equilibrados'
  
  // Guardamos en la pila los elementos positivos para
  // los cuales no hemos encontrado aún su negativo. En la
  // cima está el más recientemente encontrado; en la base
  // el menos reciente.
  stack<int> pila;
  
  // Recorremos la lista
  auto it = lista.begin();
  while (it != lista.end()) {
    if (*it > 0) {
      // Si es un número positivo, lo añadimos a la pila
      pila.push(*it);
      it++;
    } else if (*it < 0) {
      // Si es un número negativo:
      if (!pila.empty() && pila.top() == -(*it)) {
        // Si su opuesto está en la cima de
        // la pila, todo bien. Desapilamos.
        pila.pop();
        it++;
      } else {
        // Si no, es un número negativo que no tiene
        // compañero. Lo borramos de la lista
        it = lista.erase(it);
      }
    } else {
      // Si es un 0, rellenamos con el opuesto de la
      // cima de la pila, y desapilamos.
      *it = -pila.top();
      pila.pop();
      it++;
    }
  }
  
  // Rellenamos con los opuestos de todos los positivos
  // que nos han sobrado en la pila.
  while (!pila.empty()) {
    lista.push_back(-pila.top());
    pila.pop();
  }

}


// Función que trata un caso de prueba.
bool tratar_caso() {
  int num_elems;
  list<int> lista;
  
  cin >> num_elems;
  if (cin.eof()) return false;
  
  // Leemos lista
  for (int i = 0; i < num_elems; i++) {
    int elem;
    cin >> elem;
    lista.push_back(elem);
  }

  // Llamamos a la función pedida
  reconstruir(lista);
  
  // Imprimimos el resultado
  bool primero = true;
  for (auto x : lista) {
    cout << (primero ? "" : " ") << x;
    primero = false;
  }
  cout << "\n";
    
  return true;
}


int main() {
  // Ejecutamos tratar_caso() hasta que nos devuelva `false`
  while (tratar_caso()) { }
  return 0;
}
