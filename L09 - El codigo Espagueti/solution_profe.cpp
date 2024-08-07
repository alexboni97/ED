/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*  
  El código espagueti
  Manuel Montenegro Montes
*/



#include <iostream>
#include <fstream>
#include <cassert>
#include <map>

using namespace std;

struct instruccion {
  string tipo;
  string argumento;
};

using programa = map<int, instruccion>;
using memoria = map<string, int>;


// Función para ejecutar un programa.
//
// Recibe:
//    - El programa `p` a ejecutar
//    - Máximo número de instrucciones a ejecutar. Si se intenta ejecutar un número mayor
//      de instrucciones, se detiene la ejecución y se devuelve la memoria correspondiente
//      al estado del programa en el momento de detenerse.
//
// Devuelve un par con dos componentes:
//    - El estado de la memoria tras la ejecución del programa, bien sea porque se haya
//      ejecutado la última instrucción, o bien porque se haya alcanzado el límite de
//      instrucciones ejecutadas indicado por el parámetro `max_pasos`.  
//    - Un booleano que indique si se ha producido un error en la ejecución del programa
//      Devuelve `true` si se ha encontrado ejecutar una instrucción "GOTO n", donde n
//      es un número de instrucción que no se encuentra en el programa. Devuelve `false`
//      en caso contrario. Si el valor de esta componente es `true`, la primera componente
//      del par es irrelevante.

// El coste es O(M log N), donde M es el valor de `max_pasos` y N es el tamaño
// del programa `p` pasado como parámetro. Tenemos un bucle que se ejecuta,
// como mucho, M veces. En cada ejecución del bucle, en el caso peor, se
// llama al método `find` sobre `p`, que tiene coste O(log N). También
// aparece la expresión `result[var]` que también tiene coste logarítimico
// sobre el tamaño de la memoria, pero el número de variables en la memoria
// es, como mucho, igual al tamaño del programa (porque todas las variables
// de la memoria aparecen en el texto del programa). Por tanto, el coste de
// acceder a `result[var]` también es O(log N).
pair<memoria, bool> ejecutar(const programa &p, int max_pasos) {
  memoria result;
  // `it` indica la próxima instrucción a ejecutar. Comenzamos con la primera
  // del programa
  auto it = p.begin();
  // Contador de instrucciones ejecutadas.
  int cont_pasos = 0;
  bool error = false;

  // Repetimos mientras:
  //    - No hayamos sobrepasado el máximo de instrucciones a ejecutar (`max_pasos`)
  //    - No hayamos llegado al final del programa
  //    - No se haya producido un error
  while (cont_pasos < max_pasos && it != p.end() && !error) {
    // Miramos si la instrucción es de salto o de incremento
    if (it->second.tipo == "GOTO") {
      // Si es de salto, obtenemos un iterador al destino del salto
      int dest = stoi(it->second.argumento);
      auto it_dest = p.find(dest);  // O(log N)
      // Si no se encuentra el destino, activamos el booleano de error. En
      // caso contrario, actualizamos el contador de programa.
      if (it_dest == p.end()) {
        error = true;
      } else {
        it = it_dest;
      }
    } else {
      // Si es de incremento, buscamos la variable a incrementar
      string var = it->second.argumento;
      result[var]++;
      // Saltamos a la siguiente instrucción
      it++;
    }
    cont_pasos++;
  }

  return {result, error};
}


bool tratar_caso() {
  string cmd;
  cin >> cmd;

  if (cin.eof()) return false;
  
  programa p;
  while (cmd != "BYE") {
    if (cmd == "RUN") {
      int num_pasos; cin >> num_pasos;
      auto [m, error] = ejecutar(p, num_pasos);
      if (error) {
        cout << "ERROR" << "\n";
      } else {
        for (auto &[variable, valor]: m) {
          cout << variable << " = " << valor << "\n";
        }
        cout << "OK\n";
      }
    } else {
      int num_linea = stoi(cmd);
      string instruccion, parametro;
      cin >> instruccion >> parametro;
      p[num_linea] = {instruccion, parametro};
    }

    cin >> cmd;
  }
  cout << "---\n";

  return true;
}


int main() {
  // Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
  while (tratar_caso()) { }
  return 0;
}
