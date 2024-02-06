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
  Componente 1:
  Componente 2:
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>


using namespace std;

// Define aquí la clase ToeplitzMatrix e implementa sus métodos.
//
// No te olvides de indicar y justificar el coste del constructor y el coste de cada método.


bool tratar_caso() {
  // Implementa el código para tratar un caso de prueba.

  // Esta función debe devolver `false` si, en lugar de un caso de prueba,
  // se ha encontrado con la marca de fin de entrada (0 0 0).

  // En caso contrario, debe procesar el caso de prueba y devolver `true`.
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
