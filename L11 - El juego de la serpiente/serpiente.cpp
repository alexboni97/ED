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
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

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
  Posicion operator+(Direccion dir){
    if(dir==Direccion::Norte)
      y+=1;
    if(dir==Direccion::Este)
      x+=1;
    if(dir==Direccion::Sur)
      y-=1;
    if(dir==Direccion::Oeste)
      x-=1;
    return Posicion(x,y);
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

Direccion contrariaDir(Direccion dir){
  if(dir==Direccion::Este)
  return Direccion::Oeste;
  if(dir==Direccion::Oeste)
  return Direccion::Este;
  if(dir==Direccion::Norte)
  return Direccion::Sur; 
  if(dir==Direccion::Sur)
  return Direccion::Norte;
}
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
    if(serpientes.count(nombre)!=0)
      throw domain_error("ERROR: Serpiente ya existente");
    if( objetos.find(posicion)!=objetos.end())
      throw domain_error("ERROR: Posicion ocupada");
    objetos.insert({posicion,Elemento::Serpiente});
    InfoSerpiente s;
    queue <Posicion>cola;
    cola.push(posicion);
    s.cola=cola;
    s.tam=1;
    s.puntuacion=0;
    serpientes.insert({nombre,s});
  }

  void nueva_manzana(const Posicion &posicion, int crecimiento, int puntuacion) {
    if( objetos.find(posicion)!=objetos.end())
      throw domain_error("ERROR: Posicion ocupada");
    InfoManzana m;
    m.crecimiento=crecimiento;
    m.puntuacion=puntuacion;
    objetos.insert({posicion,Elemento::Manzana});
    manzanas.insert({posicion,m});
  }

  int puntuacion(const string &nombre) const {
    auto it =serpientes.find(nombre);
    if(it==serpientes.end())
      throw domain_error("ERROR: Serpiente no existe");
    return (*it).second.puntuacion;
  }
  


  bool avanzar(const string &nombre, const Direccion &dir) {
    bool pudo=true;
    auto it =serpientes.find(nombre);
    if(it==serpientes.end())
      throw domain_error("ERROR: Serpiente no existe");
    Posicion pos=(*it).second.cola.front();
    pos=pos+dir;
    auto ito=objetos.find(pos);
    if(ito==objetos.end()){
      if((*it).second.crecimiento==0)
        (*it).second.cola.pop();
      else (*it).second.crecimiento--;
      (*it).second.cola.push(pos);
    }else{
      if((*ito).second==Elemento::Manzana){
        auto itm=manzanas.find((*ito).first);
        (*it).second.puntuacion+=(*itm).second.puntuacion;
        (*it).second.crecimiento+=(*itm).second.crecimiento;
        objetos.insert_or_assign((*ito).first,Elemento::Serpiente);
        manzanas.erase(itm);
        (*it).second.cola.pop();
        (*it).second.cola.push(pos);
      }
      else {
        if((*it).second.cola.back()==(*ito).first&&(*it).second.crecimiento==0&&(*it).second.finalDir!=contrariaDir(dir)){
          (*it).second.cola.pop();
          (*it).second.cola.push(pos);
        }else{
          throw domain_error((*it).first+"muere");
        }
      }
    }
      

    return pudo;
  }

  Elemento que_hay(const Posicion &p) const {
    auto it= objetos.find(p);
    if(it==objetos.end())
      return Elemento::Nada;
    else return (*it).second;
  }

private:
  // Añade los atributos y funciones privadas que veas necesarias.
  //objetos en el tablero
  unordered_map <Posicion,Elemento,hash<Posicion>>objetos;

  //serpientes en el tablero
  struct InfoSerpiente{
    int puntuacion;
    int tam;
    queue<Posicion>cola;
    unordered_set<Posicion,hash<Posicion>>posicionesCola;
    int crecimiento;
    Direccion finalDir;
  };
  unordered_map <string,InfoSerpiente>serpientes;
 
  //manzanas en el tablero
  struct InfoManzana{
    int crecimiento=0;
    int puntuacion=0;
  };
  unordered_map<Posicion,InfoManzana,hash<Posicion>>manzanas;

};


// Función para tratar un caso de prueba. Devuelve false si, en lugar de un
// caso de prueba, se ha encontrado con la marca de fin de entrada
// (EOF). Devuelve true en caso contrario.
bool tratar_caso() {
  // Implementar
    string p;
    cin >> p;
    if (!cin)
        return false;
    JuegoSerpiente juego;
    while (p != "FIN") {
        string nombre;
        Posicion pos;
        int x, y;
        if (p == "nueva_serpiente") {
            cin >> nombre >> x >> y;
            pos = Posicion(x, y);
            juego.nueva_serpiente(nombre, pos);
        }
        else if (p == "nueva_manzana") {
            int crecimiento, puntuacion;
            cin >> nombre >> x >> y >> crecimiento >> puntuacion;
            pos = Posicion(x, y);
            juego.nueva_manzana(pos, crecimiento, puntuacion);
        }
        else if (p == "avanzar") {
            Direccion dir;
            cin >> nombre >> dir;
            juego.avanzar(nombre, dir);
        }
        else if (p == "que_hay") {
            cin >> x >> y;
            pos = Posicion(x, y);
            juego.que_hay(pos);
        }

        cin >> p;
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