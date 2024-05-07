/*
 * ---------------------------------------------------------------
 *                       ESTRUCTURAS DE DATOS
 * ---------------------------------------------------------------
 */
 
 
//@ <answer>

// Nombre y apellidos: ________________________________________  

//@ </answer>
 

//@ <answer>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <set>
#include <unordered_map>
#include <map>

// Añade los #include que necesites
//@ </answer>


using namespace std;

//@ <answer>

// Implementa los métodos pedidos dentro de la clase.
// No te olvides del coste de cada método.

class Ferrovistan {
public:

  void nueva_linea(const string &nombre) {

  }
  
  void nueva_estacion(const string &linea, const string &nombre, int posicion) {

  }
  
  void eliminar_estacion(const string &estacion) {

  }
  
  vector<string> lineas_de(const string &estacion) const {

  }
  
  
  string proxima_estacion(const string &linea, const string &estacion) const {

  }

private:
  struct Lineas{

  };
  struct Estaciones{

  };
  unordered_map<Lineas,set<Estaciones>>estaciones;
  unordered_map<Lineas,set<Estaciones>>lineas;
  
  map<int,string>linea;
  map<string,int>estacion;
};



//---------------------------------------------------------------
// No modificar nada por debajo de esta línea
// -------------------------------------------------------------
//@ </answer>

bool tratar_caso() {
  Ferrovistan f;
  string operacion;
  cin >> operacion;
  
  if (cin.eof()) return false;
  
  while (operacion != "FIN") {
    try {
      if (operacion == "nueva_linea") {
        string nombre; cin >> nombre;
        f.nueva_linea(nombre);
      } else if (operacion == "nueva_estacion") {
        string linea; cin >> linea;
        string nombre; cin >> nombre;
        int posicion; cin >> posicion;
        f.nueva_estacion(linea, nombre, posicion);
      } else if (operacion == "eliminar_estacion") {
        string estacion; cin >> estacion;
        f.eliminar_estacion(estacion);
      } else if (operacion == "lineas_de") {
        string estacion; cin >> estacion;
        vector<string> lineas = f.lineas_de(estacion);
        cout << "Lineas de " << estacion << ":";
        for (const string &linea: lineas) {
          cout << " " << linea;
        }
        cout << "\n";
      } else if (operacion == "proxima_estacion") {
        string linea; cin >> linea;
        string estacion; cin >> estacion;
        string proxima = f.proxima_estacion(linea, estacion);
        cout << proxima << "\n";
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
#ifndef DOMJUDGE
  std::ifstream in("sample3.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while(tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
