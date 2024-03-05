/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */


/*
 * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas está
 * prohibida, pues no se tendrá en cuenta para la corrección.
 *
 * Tampoco esta permitido modificar las líneas que contienen
 * las etiquetas <answer> y </answer>, obviamente :-)
 */  


//@ <answer>
/*  
  Indica el nombre y apellidos de los componentes del grupo
  ---------------------------------------------------------
  Componente 1: ALEX GUILLERMO BONILLA TACO 
  Componente 2: BRYAN EDUARDO CORDOVA ASCURRA
*/
//@ </answer>

 
// Añade los #include que necesites
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <list>
#include <stack>

using namespace std;


//@ <answer>
// Implementa la función pedida aquí.
// Para ello utiliza las librerías de la STL.
//
// No olvides justificar brevemente el coste.
//
/*
la funcion reconstruir tiene coste en tiempo O(n) puesto que tiene dos bucles no anidados(uno para recorrer la lista y otro para vaciar la pila).
El coste en espacio en el caso peor(todos positivos) es O(2n) que es equivalente a O(n) 
siendo n el numero de elementos que tiene la lista que se pasa por parametro.
La estructura auxilar (pila) todas sus operaciones son de coste cte O(1) y 
el bucle while() que usamos para recorrer la lista todas las operaciones internas son de coste cte O(1)
*/

void reconstruir(list<int> &lista) {
  auto it = lista.begin();
  stack<int> pila;
  
  while(it!=lista.end()){
    if(*it > 0) {
      pila.push(*it);
    it++;

    }
    else if(*it==0){
      if(pila.top() > 0) {
        *it = -(pila.top());
      }
      pila.pop();
      it++;

    }
    else if(*it < 0){
      if (pila.empty() || pila.top() != -(*it)) {
        it=lista.erase(it);
      }
      else {
        pila.pop();
        it++;
      }
      
    }
  }

  while(!pila.empty()) {
    lista.push_back(-pila.top());
    pila.pop();
  } 
}

//---------------------------------------------------------------
// No modificar nada por debajo de esta línea
// -------------------------------------------------------------
//@ </answer>


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
  // Si estás ejecutando el programa en tu ordenador, las siguientes líneas
  // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
  // útil para no tener que teclear los casos de prueba por teclado cada vez
  // que ejecutas el programa.
  //
  // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
  // comenta las líneas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  // Ejecutamos tratar_caso() hasta que nos devuelva `false`
  while (tratar_caso()) { }

  // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
