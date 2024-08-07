/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */



// Solución al problema L12 - El juego de la Serpiente (2ª parte)
// Manuel Montenegro Montes


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
    // No hacemos nada
  }

  // Coste: O(log S), donde S es el número de serpientes
  void nueva_serpiente(const string &nombre, const Posicion &posicion) {
    if (serpientes.count(nombre)) {
      throw domain_error("Serpiente ya existente");
    }
    if (ocupadas.count(posicion) || manzanas.count(posicion)) {
      throw domain_error("Posicion ocupada");
    }

    // Creamos la nueva serpiente, que únicamente contiene su cabeza
    queue<Posicion> q; q.push(posicion);
    // Insertamos la serpiente al final de la lista de serpientes que tienen
    // puntuación 0, y obtenemos un iterador a esa posición
    auto it = ranking[0].insert(ranking[0].end(), nombre);      // O(log S)
    // Insertamos la serpiente en el diccionario de serpientes
    serpientes.insert({nombre, {posicion, 0, 0, q, it}});
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
  // Coste amortizado: O(log S), ya que eliminar una serpiente de longitud N ha
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


  // O(min{num, S}), donde S es el número de serpientes
  // El coste es proporcional al número de llamadas totales a `result.push_back` dentro 
  // del bucle interno.
  // Si S < num, se insertan en `result` solamente S serpientes.
  // Si S > num, se insertan en `result` solamente num serpientes.
  vector<pair<string, int>> mejores_puntuaciones(int num) const {    
    int n = 0;  // Contador de puntuaciones insertadas en el resultado
    vector<pair<string, int>> result;

    auto it_ranking = ranking.begin();
    while (it_ranking != ranking.end() && n < num) {  // Recorremos el diccionario ranking
      int puntuacion = it_ranking->first;
      auto it_list = it_ranking->second.begin();

      // Para cada puntuación, recorremos las serpientes con esa puntuación
      while (it_list != it_ranking->second.end() && n < num) {
        result.push_back({*it_list, puntuacion});
        n++;
        it_list++;
      }

      it_ranking++;
    }
    return result;
  }


private:

  // Para cada serpiente almacenamos:
  //  - La posición de su cabeza
  //  - Su puntuación
  //  - El temporizador de crecimiento
  //  - Una cola que contiene todas las casillas que ocupa el cuerpo de la serpiente
  //  - Iterador a la lista correspondiente dentro del ranking
  struct Serpiente {
    Posicion cabeza;
    int puntuacion;
    int temp_crecimiento;
    queue<Posicion> cuerpo;
    list<string>::iterator it_puntuacion;    
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

  // Para cada puntuación, lista de serpientes que tienen esa puntuación.
  // Utilizamos greater<int> como tercer parámetro para que el diccionario
  // se recorra en orden descendente de puntuación.  
  map<int, list<string>, std::greater<int>> ranking;


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
  // Coste amortizado: O(log S), ya que eliminar una serpiente de longitud N ha
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
      ranking[s.puntuacion].erase(s.it_puntuacion);   // O(log S), por el acceso a `ranking`
      if (ranking[s.puntuacion].empty()) {      // O(log S), por el acceso a `ranking`
        ranking.erase(s.puntuacion);            // O(log S)
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
      if (manzanas.count(sig)) {
        Manzana m = manzanas.at(sig);
        manzanas.erase(sig);
        int antigua_puntuacion = s.puntuacion;
        s.puntuacion += m.puntuacion;

        if (antigua_puntuacion != s.puntuacion) {
          // Borramos a la serpiente de la lista de su puntuación antigua
          ranking[antigua_puntuacion].erase(s.it_puntuacion);   // O(log S), por el acceso a `ranking`
          // Si era la última serpiente con esa puntuación, borramos esa puntuación
          // del ranking
          if (ranking[antigua_puntuacion].empty()) {      // O(log S), por el acceso a `ranking`
            ranking.erase(antigua_puntuacion);            // O(log S)
          }
          auto nuevo_it = ranking[s.puntuacion].insert(ranking[s.puntuacion].end(), nombre);  // O(log S)
          s.it_puntuacion = nuevo_it;
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
      } else if (operacion == "mejores_puntuaciones") {
        int num;
        cin >> num;
        vector<pair<string, int>> mejores = s.mejores_puntuaciones(num);
        cout << "Las " << mejores.size() << " mejores puntuaciones:\n";
        for (auto &[nombre, punt] : mejores) {
          cout << "  " << nombre << " (" << punt << ")\n";
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


int main() {
  // Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
  while (tratar_caso()) { }

  // Comenta esto también si has comentado lo anterior.
  return 0;
}
