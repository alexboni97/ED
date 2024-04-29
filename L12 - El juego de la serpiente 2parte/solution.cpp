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
  Componente 1:
  Componente 2:
*/
//@ </answer>


// Añade los #include que necesites
#include <iostream>
#include <fstream>
#include <cassert>
#include <queue>

using namespace std;

// Tipo para representar una posición en la cuadrícula mediante un par de
// coordenadas
struct Posicion {
  int x, y;

  Posicion(): Posicion(0, 0) { }
  Posicion(int x, int y): x(x), y(y) { }

  bool operator==(const Posicion &other) const {
    return x == other.x && y == other.y;
  }
};

// Definimos una función hash para el tipo Posicion.
template<>
class std::hash<Posicion> {
public:
  int operator()(const Posicion &p) const {
    return p.x ^ (p.y << 1);
  }
};


// Tipo de datos enumerado para representar direcciones
enum class Direccion { Norte, Sur, Este, Oeste };

// Sobrecargamos el operador >> para poder leer direcciones más fácilmente.
// Bastará con hacer `cin >> d` donde `d` es una variable de tipo Direccion.
istream &operator>>(istream &in, Direccion &d) {
  string s; in >> s;
  if (s == "N") {
    d = Direccion::Norte;
  } else if (s == "S") {
    d = Direccion::Sur;    
  } else if (s == "E") {
    d = Direccion::Este;
  } else if (s == "O") {
    d = Direccion::Oeste;
  }
  return in;
}

// Tipo de datos enumerado para representar elementos del tablero
enum class Elemento { Manzana, Serpiente, Nada };

// Sobrecargamos el operador << para poder escribir elementos del tablero más
// fácilmente. Bastará con hacer `cout << e` donde `e` es una variable de
// tipo Elemento.
ostream &operator<<(ostream &out, const Elemento &e) {
  switch (e) {
  case Elemento::Manzana: out << "MANZANA"; break;
  case Elemento::Serpiente: out << "SERPIENTE"; break;
  case Elemento::Nada: out << "NADA"; break;
  }
  return out;
}


//--------------------------------------------------------------------------
// Modificar a partir de aquí
//--------------------------------------------------------------------------
//@ <answer>

// TAD para el juego de la serpiente. Implementa cada una de las operaciones,
// y justifica su coste.
class JuegoSerpiente {
public:
  JuegoSerpiente() {

  }

  void nueva_serpiente(const string &nombre, const Posicion &posicion) {

  }

  void nueva_manzana(const Posicion &posicion, int crecimiento, int puntuacion) {

  }

  int puntuacion(const string &nombre) const {

  }
  
  bool avanzar(const string &nombre, const Direccion &dir) {

  }

  Elemento que_hay(const Posicion &p) const {

  }

  vector<pair<string, int>> mejores_puntuaciones(int num) const {    

  }

private:
  // Añade los atributos y funciones privadas que veas necesarias.

};


// Función para tratar un caso de prueba. Devuelve false si, en lugar de un
// caso de prueba, se ha encontrado con la marca de fin de entrada
// (EOF). Devuelve true en caso contrario.
bool tratar_caso() {
  // Implementar
}


//@ </answer>
//--------------------------------------------------------------------------
// No modificar a partir de aquí
//--------------------------------------------------------------------------


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

  // Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
  while (tratar_caso()) { }

  // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
