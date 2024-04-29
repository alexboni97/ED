/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>

using namespace std;

class ConteoVotos {
public:

  void nuevo_estado(const string &nombre, int num_compromisarios) {
    if (estados.count(nombre)) {
      throw domain_error("Estado ya existente");
    }
    estados.insert({nombre, {num_compromisarios}});
  }


  void sumar_votos(const string &estado, const string &partido, int num_votos) {
    InfoEstado &ie = buscar_estado(estado);
    ie.votos_de_partido[partido] += num_votos;
    // Si al sumar los votos, los votos del partido pasado como parámetro superan
    // al número de votos del ganador, tenemos que actualizar el partido ganador.
    if (ie.votos_de_partido[partido] > ie.votos_de_partido[ie.ganador]) {
      string antiguo_ganador = ie.ganador;
      ie.ganador = partido;
      // El partido pasado como parámetro gana los compromisarios de ese estado
      partidos[partido] += ie.num_compromisarios;
      if (antiguo_ganador != "") {
        // Y el antiguo ganador pierde los compromisarios de ese estado
        partidos[antiguo_ganador] -= ie.num_compromisarios;
        // Además, si se queda sin compromisarios, lo eliminamos del diccionario
        // de partidos.
        if (partidos[antiguo_ganador] == 0) partidos.erase(antiguo_ganador);
      }
    }
  }


  string ganador_en(const string &estado) const {
    return buscar_estado(estado).ganador;
  }


  vector<pair<string,int>> resultados() const {
    vector<pair<string, int>> result(partidos.size());



    copy(partidos.begin(), partidos.end(), result.begin());

    return result;
  }

private:
  // Información asociada a cada estado
  struct InfoEstado {
    // Número de compromisarios en el colegio electoral
    int num_compromisarios;   

    // Número de votos obtenidos por cada partido en ese estado
    unordered_map<string, int> votos_de_partido;

    // Partido que tiene más votos en ese estado
    string ganador;

    InfoEstado(int nc): num_compromisarios(nc), votos_de_partido(), ganador("") { }
  };

  // Almacenamos, para cada estado, una instancia de InfoEstado
  unordered_map<string, InfoEstado> estados;

  // Almacenamos, para cada partido, el número total de compromisarios
  // que ha ganado. Este número es la suma de los compromisarios de los
  // estados en los que tiene mayoría. Utilizamos map en lugar de unordered_map
  // porque en el método resultados() vamos a tener que recorrer este
  // diccionario en orden ascendente por nombre de partido
  map<string, int> partidos;


  InfoEstado & buscar_estado(const string &nombre) {
    auto it = estados.find(nombre);
    if (it == estados.end()) {
      throw domain_error("Estado no encontrado");
    }
    return it->second;
  }


  const InfoEstado & buscar_estado(const string &nombre) const {
    auto it = estados.find(nombre);
    if (it == estados.end()) {
      throw domain_error("Estado no encontrado");
    }
    return it->second;
  }  

};


bool tratar_caso() {
  // Completar
//{{{
  string comando;
  cin >> comando;
  if (cin.eof()) return false;

  ConteoVotos cv;

  while (comando != "FIN") {
    try {
      if (comando == "nuevo_estado") {
        string estado;
        int num_compromisarios;
        cin >> estado >> num_compromisarios;
        cv.nuevo_estado(estado, num_compromisarios);
      } else if (comando == "sumar_votos") {
        string estado;
        string partido;
        int num_votos;
        cin >> estado >> partido >> num_votos;
        cv.sumar_votos(estado, partido, num_votos);
      } else if (comando == "ganador_en") {
        string estado;
        cin >> estado;
        string ganador  = cv.ganador_en(estado);
        cout << "Ganador en " << estado << ": " << ganador << "\n";
      } else if (comando == "resultados") {
        for (const auto &[partido, num_comp] : cv.resultados()) {
          cout << partido << " " << num_comp << "\n";
        }
      }
    } catch (std::exception &e) {
      cout << e.what() << "\n";
    }
    cin >> comando;
  }

  cout << "---\n";
  return true;
//}}}
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}