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
#include <iterator>

// Añade los #include que necesites
//@ </answer>


using namespace std;

//@ <answer>

// Implementa los métodos pedidos dentro de la clase.
// No te olvides del coste de cada método.

class Ferrovistan {
public:

  void nueva_linea(const string &nombre) {
    auto it=lineas.find(nombre);
    if(it!=lineas.end())
      throw domain_error("Linea existente");
    lineas[nombre];
  }
  
  void nueva_estacion(const string &linea, const string &nombre, int posicion) {
    auto it=lineas.find(linea);
    if(it==lineas.end())
      throw domain_error("Linea no existente");
    auto itE=estaciones.find(nombre);
    if(itE!=estaciones.end())
      throw domain_error("Estacion duplicada en linea");
    auto posiciones=it->second;
    auto itP=posiciones.find(posicion);
    if(itP!=posiciones.end())
      throw domain_error("Posicion Ocupada");
    posiciones[posicion]=nombre;
    estaciones[nombre][linea]=posicion;
  }
  
  void eliminar_estacion(const string &estacion) {
    auto it=estaciones.find(estacion);
    if(it==estaciones.end())
      throw domain_error("Estacion no existe");
    auto lineas_activas=it->second;
    for(auto linea:lineas_activas){
      lineas[linea.first].erase(linea.second);
    }
    estaciones.erase(estacion);
  }
  
  vector<string> lineas_de(const string &estacion) const {
    vector<string> collect ;
    auto it=estaciones.find(estacion);
    if(it==estaciones.end())
      throw domain_error("Estacion no existente");
    for(auto l:it->second){
      collect.push_back(l.first);
    }
    return collect;
  }
  
  
  string proxima_estacion(const string &linea, const string &estacion) const {
    auto it = lineas.find(linea);
    if (it == lineas.end())
      throw domain_error("Linea no existente");
    auto itE = estaciones.find(estacion);
    if (itE == estaciones.end())
      throw domain_error("Estacion no existente");
    auto itffff=itE;
    ++itffff;
    if(itffff==estaciones.end())
      throw domain_error("Fin de trayecto");
    int posicion=itE->second.find(linea)->second;
    return (++(it->second.find(posicion)))->second;
  }

private:
  using Linea=string;
  using Estacion=string;
  using Distancia=int;
  //unordered_map<Estacion,set<Linea>>estaciones;
  unordered_map<Estacion,map<Linea,Distancia>>estaciones;
  unordered_map<Linea,map<Distancia,Estacion>>lineas;;
  
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
  std::ifstream in("sample.in");
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
