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
#include <cassert>
#include <queue>
 
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>

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

// TAD para el juego de la serpiente.
class JuegoSerpiente {
public:
  // Coste: O(1)
  JuegoSerpiente() {
    ranking.insert(0, {});
  }

  // Coste: O(1)
  void nueva_serpiente(const string &nombre, const Posicion &posicion) {
    if (serpientes.count(nombre)) {
      throw domain_error("Serpiente ya existente");
    }
    if (ocupadas.count(posicion) || manzanas.count(posicion)) {
      throw domain_error("Posicion ocupada");
    }

    // Creamos la nueva serpiente, que únicamente contiene su cabeza
    queue<Posicion> q; q.push(posicion);
    serpientes.insert({nombre, {posicion, 0, 0, q}});

    ranking.insert({0,{nombre}});
    // La posición pasa a estar ocupada
    ocupadas.insert(posicion);
  }

  // Coste: O(1)
  void nueva_manzana(const Posicion &posicion, int crecimiento, int puntuacion) {
    if (manzanas.count(posicion) || ocupadas.count(posicion)) {
      throw domain_error("Posicion ocupada");
    }
    manzanas.insert({posicion, {crecimiento, puntuacion}});
  }

  // Coste: O(1)
  int puntuacion(const string &nombre) const {
    return buscar_serpiente(nombre).puntuacion;
  }
  
  // Coste: O(N) en el caso peor, donde N es la longitud de la serpiente.
  // Coste amortizado: O(1), ya que eliminar una serpiente de longitud N ha
  // venido precedido de N llamadas a `avanzar` en las que la serpiente crecía.
  bool avanzar(const string &nombre, const Direccion &dir) {
    Serpiente &s = buscar_serpiente(nombre);
    return mover_serpiente(s, nombre, dir);
  }

  // Coste: O(1)
  Elemento que_hay(const Posicion &p) const {
    if (ocupadas.count(p)) {
      return Elemento::Serpiente;
    } else if (manzanas.count(p)) {
      return Elemento::Manzana;
    } else {
      return Elemento::Nada;
    }
  }
  vector<pair<string, int>> mejores_puntuaciones(int num) const {    
    int i=0;
    auto itr=ranking.begin();
    vector<pair<string, int>>vpuntuaciones;
    while (itr!=ranking.end()&&i<num){
      map<int,string>rankEnPosI=(*itr).second;
      for(auto itrr=rankEnPosI.begin();itrr!=rankEnPosI.end();itrr++){
        vpuntuaciones[i]={(*itrr).second,(*itr).first};
      }
       i++;
    }
    return vpuntuaciones;
    
  }

private:

  // Para cada serpiente almacenamos:
  //  - La posición de su cabeza
  //  - Su puntuación
  //  - El temporizador de crecimiento
  //  - Una cola que contiene todas las casillas que ocupa el cuerpo de la serpiente
  struct Serpiente {
    Posicion cabeza;
    int puntuacion;
    int temp_crecimiento;
    queue<Posicion> cuerpo;
  };

  // Para cada manzana almacenamos:
  //  - Cuánto hace crecer a la serpiente que se la come
  //  - Los puntos que recibe la serpiente que se la come
  struct Manzana {
    int crecimiento;
    int puntuacion;
  };

  // Diccionario que almacena la información de cada serpiente
  unordered_map<string, Serpiente> serpientes;
  // Diccionario que almacena la posición de cada manzana
  unordered_map<Posicion, Manzana> manzanas;
  // Conjunto que indica las posiciones que están ocupadas por
  // serpientes
  unordered_set<Posicion> ocupadas;
//ranking de puntuaciones y cada puntuacion tiene un ranking de llegad
  map<int,list<string>>ranking;

  

  // Dada una dirección como punto cardinal (N, S, E, O), devuelve un vector
  // unitario que apunta en esa dirección.
  // Coste: O(1)
  static pair<int, int> vector_unitario(const Direccion &d) {
    switch (d) {
    case Direccion::Norte: return {0, 1};
    case Direccion::Sur: return {0, -1};
    case Direccion::Este: return {1, 0};
    default: return {-1, 0};
    }
  }

  // Busca la información relativa a una serpiente, o lanza una excepción
  // en caso de no encontrarla.
  const Serpiente &buscar_serpiente(const string &nombre) const {    
    auto it = serpientes.find(nombre);
    if (it == serpientes.end()) {
      throw domain_error("Serpiente no existente");
    } else {
      return it->second;
    }
  }

  // Busca la información relativa a una serpiente, o lanza una excepción
  // en caso de no encontrarla.
  // Coste: O(1)
  Serpiente &buscar_serpiente(const string &nombre) {
    auto it = serpientes.find(nombre);
    if (it == serpientes.end()) {
      throw domain_error("Serpiente no existente");
    } else {
      return it->second;
    }
  }

  // Realiza el movimiento de una serpiente en una determinada dirección
  // Coste: O(N) en el caso peor, donde N es la longitud de la serpiente.
  // Coste amortizado: O(1), ya que eliminar una serpiente de longitud N ha
  // venido precedido de N llamadas a `avanzar` en las que la serpiente crecía.
  bool mover_serpiente(Serpiente &s, const string &nombre, const Direccion &dir) {
    // Calculamos la siguiente posición de la cabeza
    auto [dir_x, dir_y] = vector_unitario(dir);
    Posicion sig = { s.cabeza.x + dir_x, s.cabeza.y + dir_y };

    // Hacemos avanzar el cuerpo de la serpiente, y la hacemos crecer
    // en caso de que toque
    if (s.temp_crecimiento == 0) {
      // Si la serpiente no está creciendo, la cola de la serpiente se
      // desplaza una posición, dejando libre la casilla que ocupaba
      ocupadas.erase(s.cuerpo.front());
      s.cuerpo.pop();
    } else {
      // Si la serpiente está creciendo, la cola de la serpiente se queda como
      // está, pero disminuye el temporizador de crecimiento.
      s.temp_crecimiento--;
    }

    // Comprobamos si, tras mover la cola, la nueva posición de la
    // cabeza está ocupada por otra serpiente o por sí misma.
    if (ocupadas.count(sig)) {
      // Si está ocupada, la serpiente muere. Hay que retirar
      // su cuerpo del tablero
      while (!s.cuerpo.empty()) {
         ocupadas.erase(s.cuerpo.front());
         s.cuerpo.pop();
      }
      // Borramos la serpiente del diccionario.
      serpientes.erase(nombre);
      return true;
    } else {
      // Si la casilla está libre, actualizamos la cabeza de la serpiente
      // y marcamos la casilla como ocupada.
      s.cabeza = sig;
      s.cuerpo.push(sig);
      ocupadas.insert(sig);

      // Si hay una manzana en la nueva posición, la quitamos del tablero y
      // cambiamos los atributos de la serpiente.
      list<string> l;
      if (manzanas.count(sig)) {
        Manzana m = manzanas.at(sig);
        manzanas.erase(sig);
        s.puntuacion += m.puntuacion;
        auto itr =ranking.find(s.puntuacion);
        if(itr!=ranking.end()){
          l.push_back(nombre);
          ranking.insert_or_assign(m.puntuacion, l);
        }else{
          if (m.puntuacion!=0) {
            l=(*itr).second;
            l.push_back(nombre);
            ranking.insert_or_assign(s.puntuacion,l);
          }
          
        }
        s.temp_crecimiento += m.crecimiento;
      }
      return false;
    }
  }

};


// Función para tratar un caso de prueba. Devuelve false si, en lugar de un
// caso de prueba, se ha encontrado con la marca de fin de entrada
// (EOF). Devuelve true en caso contrario.
bool tratar_caso() {
  string operacion;
  cin >> operacion;

  if (cin.eof()) return false;

  JuegoSerpiente s;

  while (operacion != "FIN") {
    try {
      if (operacion == "nueva_serpiente") {
        string nombre;
        int pos_x;
        int pos_y;
        cin >> nombre >> pos_x >> pos_y;
        s.nueva_serpiente(nombre, {pos_x, pos_y});
      } else if (operacion == "nueva_manzana") {
        int pos_x, pos_y, crecimiento, puntuacion;
        cin >> pos_x >> pos_y >> crecimiento >> puntuacion;
        s.nueva_manzana({pos_x, pos_y}, crecimiento, puntuacion);
      } else if (operacion == "puntuacion") {
        string nombre;
        cin >> nombre;
        int punt = s.puntuacion(nombre);
        cout << nombre << " tiene " << punt << " puntos\n";
      } else if (operacion == "avanzar") {
        string nombre; Direccion d;
        cin >> nombre >> d;
        if (s.avanzar(nombre, d)) {
          cout << nombre << " muere\n";
        }
      } else if (operacion == "que_hay") {
        int x, y;
        cin >> x >> y;
        Elemento e = s.que_hay({x, y});
        cout << e << "\n";
      } else if (operacion == "mejores_puntuaciones"){
        int n;
        cin >> n;
        vector<pair<string, int>> puntuaciones = s.mejores_puntuaciones(n); 
        for (int i = 0; i < puntuaciones.size(); i++)        {
          cout << puntuaciones[i].first << " (" << puntuaciones[i].second << ")\n";
        }     
      }
    } catch (exception &e) {
      cout << "ERROR: " << e.what() << "\n";
    }
    cin >> operacion;
  }

  cout << "---\n";
  return true;

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