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
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

using namespace std;




// Tipo de datos enumerado para representar direcciones
enum class Direccion { Norte, Sur, Este, Oeste };

Direccion mismaDir(Direccion dir){
  if(dir==Direccion::Este)
  return Direccion::Oeste;
  else if(dir==Direccion::Oeste)
  return Direccion::Este;
  else if(dir==Direccion::Norte)
  return Direccion::Sur; 
  else 
  return Direccion::Norte;
}
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
  //COSTE O(1) puesto que todas las operaciones que tiene dentro nueva_serpiente() son de coste O(1) cte por las estructuras de datos usadas
  void nueva_serpiente(const string &nombre, const Posicion &posicion) {
    if(serpientes.count(nombre)!=0)//O(1)
      throw domain_error("ERROR: Serpiente ya existente\n");
    if( objetos.find(posicion)!=objetos.end())//O(1)
      throw domain_error("ERROR: Posicion ocupada\n");
    objetos.insert({posicion,Elemento::Serpiente});//O(1)
    InfoSerpiente s;
    queue <Posicion>cola;
    cola.push(posicion);//O(1)
    s.cola=cola;
    s.puntuacion=0;
    s.crecimiento=0;
    serpientes.insert({nombre,s});//O(1)
  }

  //COSTE O(1) puesto que todas las operaciones que tiene dentro nueva_manzana() son de coste O(1) cte por las estructuras de datos usadas
  void nueva_manzana(const Posicion &posicion, int crecimiento, int puntuacion) {
    if( objetos.find(posicion)!=objetos.end())//O(1)
      throw domain_error("ERROR: Posicion ocupada\n");
    InfoManzana m;
    m.crecimiento=crecimiento;
    m.puntuacion=puntuacion;
    objetos.insert({posicion,Elemento::Manzana});//O(1)
    manzanas.insert({posicion,m});//O(1)
  }

  //COSTE O(1) puesto que todas las operaciones que tiene dentro puntuacion() son de coste O(1) cte por las estructuras de datos usadas
  int puntuacion(const string &nombre) const {
    auto its =serpientes.find(nombre);//O(1)
    if(its==serpientes.end())
      throw domain_error("ERROR: Serpiente no existente\n");
    return (*its).second.puntuacion;
  }
  


  //COSTE O(1) puesto que todas las operaciones que tiene dentro avanzar() son de coste O(1) cte por las estructuras de datos usadas
  bool avanzar(const string &nombre, const Direccion &dir) {
    bool pudo = false;
    auto its = serpientes.find(nombre);
    if (its == serpientes.end())
      throw domain_error("ERROR: Serpiente no existente\n");
    Posicion pos = (*its).second.cola.back();
    pos = pos + dir;
    auto ito = objetos.find(pos);
    if (ito == objetos.end()){
      if ((*its).second.crecimiento == 0){
        objetos.erase((*its).second.cola.front());
        (*its).second.cola.pop();
      }
      else
        (*its).second.crecimiento--;
      (*its).second.cola.push(pos);
      objetos.insert({pos, Elemento::Serpiente});
    }
    else{
      if ((*ito).second == Elemento::Manzana){
        auto itm = manzanas.find((*ito).first);
        if ((*its).second.crecimiento == 0){
          objetos.erase((*its).second.cola.front());
          (*its).second.cola.pop();
        }else
          (*its).second.crecimiento--;
        (*its).second.puntuacion += (*itm).second.puntuacion;
        (*its).second.crecimiento += (*itm).second.crecimiento;
        objetos.insert_or_assign((*ito).first, Elemento::Serpiente);
        manzanas.erase(itm);
        (*its).second.cola.push(pos);
      }
      else{
        if(((*its).second.crecimiento == 0&&(*its).second.cola.front() == (*ito).first)){//&&((*its).second.cola.size() == 2&&(*its).second.finalDir != mismaDir(dir))
            objetos.erase((*its).second.cola.front());
            (*its).second.cola.pop();
            (*its).second.cola.push(pos);
        }
        else{
          while (!(*its).second.cola.empty())
          {
            objetos.erase((*its).second.cola.front());
            (*its).second.cola.pop();
          }
          serpientes.erase((*its).first);
          return true;
        }
      }
    }

    return pudo;
  }

  //COSTE O(1) puesto que todas las operaciones que tiene dentro avanzar() son de coste O(1) cte por las estructuras de datos usadas
  Elemento que_hay(const Posicion &p) const {
    auto it= objetos.find(p);
    if(it==objetos.end())
      return Elemento::Nada;
    else return (*it).second;
  }

private:
  // Añade los atributos y funciones privadas que veas necesarias.
  //objetos en el tablero
  unordered_map <Posicion,Elemento>objetos;

  //serpientes en el tablero
  struct InfoSerpiente{
    int puntuacion;
    int crecimiento;
    queue<Posicion>cola;
  };
  unordered_map <string,InfoSerpiente>serpientes;
 
  //manzanas en el tablero
  struct InfoManzana{
    int crecimiento=0;
    int puntuacion=0;
  };
  unordered_map<Posicion,InfoManzana>manzanas;

};


// Función para tratar un caso de prueba. Devuelve false si, en lugar de un
// caso de prueba, se ha encontrado con la marca de fin de entrada
// (EOF). Devuelve true en caso contrario.
bool tratar_caso(){
  // Implementar
  string p;
  cin >> p;
  if (cin.eof() || !cin)
    return false;

  JuegoSerpiente juego;
  while (p != "FIN")  {
    try    {
      string nombre;
      Posicion pos;
      int x, y;
      if (p == "nueva_serpiente"){
        cin >> nombre >> x >> y;
        pos = Posicion(x, y);
        juego.nueva_serpiente(nombre, pos);
      }
      else if (p == "nueva_manzana"){
        int crecimiento, puntuacion;
        cin >> x >> y >> crecimiento >> puntuacion;
        pos = Posicion(x, y);
        juego.nueva_manzana(pos, crecimiento, puntuacion);
      }
      else if (p == "avanzar"){
        Direccion dir;
        cin >> nombre >> dir;
        if (juego.avanzar(nombre, dir))
          cout << nombre << " muere" << endl;
      }
      else if (p == "que_hay"){
        cin >> x >> y;
        pos = Posicion(x, y);
        cout << juego.que_hay(pos);
        cout << endl;
      }
      else if (p == "puntuacion"){
        cin >> nombre;
        int puntuacion = juego.puntuacion(nombre);
        cout << nombre << " tiene " << puntuacion << " puntos" << endl;
      }
    }
    catch (exception &e){
      cout << e.what();
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