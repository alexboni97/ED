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
#include <string>
#include <vector>
#include <cassert>

using namespace std;


const int MAX_RESERVAS = 50000;

class Teatro {
public:  

  // Constructor de la clase
  Teatro();

  // Añade aquí la cabecera de los métodos pedidos en la práctica.
  // Implementa el constructor y los métodos fuera de la clase.


private:
  struct Reserva {
    int inicio;
    int fin;
    string nombre;
  };

  vector<Reserva> reservas;
  int num_reservas;

  // Añade la cabecera de los métodos auxiliares privados que necesites
  // Impleméntalos fuera de la clase

};

// Implementación del constructor.
// Inicializamos el vector de reservas para que tenga longitud MAX_RESERVAS
// También inicializamos el atributo num_reservas a 0.

Teatro::Teatro(): reservas(MAX_RESERVAS), num_reservas(0) { }

// Implementa aquí los restantes métodos de la clase, tanto los públicos
// como los privados



bool tratar_caso() {
  // Leer y tratar un caso de prueba. Devuelve 'false' si se leyó la marca de fin
  // de entrada (0 0), o 'true' en caso contrario.
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


