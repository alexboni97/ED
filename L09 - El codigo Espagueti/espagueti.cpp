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
  Componente 1: BRYAN EDUARDO CORDOVA ASCURRA
  Componente 2: ALEX GUILLERMO BONILLA TACO
*/


// Añade los #include que necesites
#include <iostream>
#include <fstream>
#include <cassert>
#include <map>
#include <string>
#include <sstream>

using namespace std;

// En este ejercicio utilizamos la clase `map` de la librería estándar de C++, 
// en lugar de la clase MapTree vista en clase. La interfaz de `map` es casi
// la misma que la de `MapTree`. Consulta el FAQ de la práctica para ver las
// diferencias principales.

// También puedes ver la documentación de la clase `map` en:
// https://en.cppreference.com/w/cpp/container/map



// Define un tipo para representar los programas
// using programa = ...
using programa=map<int,pair<string,string>>;
// Define un tipo para almacenar el valor de cada variable del programa
// using memoria = ...
using memoria=map<string,int>;

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

// Indica el coste, en el caso peor, de la función `ejecutar`, en función del tamaño
// del programa `p` y de `num_pasos`
/*
En el caso peor, recorremos todo el map p hasta llegar a max_pasos, por lo tanto el coste sería
O(m*log n) siendo m el numero maximo de pasos (max_pasos) pasado como parametro de entrada y
log n, siendo n el numero de entradas mayor entre las que se encuentran en el map usado en programa p y las entradas del map usado en memoria m.
Este coste log n sobre el tipo map producen las operaciones find() e insert_or_assign() 
*/
pair<memoria, bool> ejecutar(const programa &p, int max_pasos){
  memoria m;
  bool running = true;
  auto it = p.begin();
  int ni = 0;

  while (ni < max_pasos && it != p.end() && running) { // O(max_pasos)
    pair<string, string> pvalue = it->second;
    if (pvalue.first == "INCR"){
      auto itm = m.find(pvalue.second); // O(log n) 
      if (itm != m.end()) { // O(1)
        m.insert_or_assign(itm->first, ++(itm->second)); // O(log n)
      }
      else{
        m.insert_or_assign(pvalue.second, 1);// O(log n)
      }
      it++;
    }
    else{
      it = p.find(stoi(pvalue.second)); // O(log n) 
      if (it == p.end())  // O(1)
        running = false;
    }
    ni++;
  }
  return {m, running};
}

void mostrarMemoria(const memoria &m){
  for (auto it = m.begin(); it != m.end(); it++){
    cout << it->first << " = " << it->second << endl;
  }
}

// Introduce el código para tratar un caso de prueba. Devuelve true
// si se ha encontrado un caso de prueba en la entrada, o false si,
// en su lugar, se ha encontrado la marca de fin de fichero (EOF).
bool tratar_caso() {
  programa p;
  string linea, sfirst;

  getline(std::cin, linea);
  if (linea == ""){
    return false;
  }
  stringstream ss(linea);
  ss >> sfirst;
  while (sfirst != "BYE"){
    if (sfirst == "RUN"){
      int np;
      ss >> np;
      pair<memoria, bool> solRun = ejecutar(p, np);
      if (solRun.second){
        mostrarMemoria(solRun.first);
        cout << "OK\n";
      }
      else
        cout << "ERROR\n";
    }
    else{
      int ni = stoi(sfirst);
      pair<string, string> value;
      ss >> value.first;
      ss >> value.second;
      p.insert_or_assign(ni, value);
    }
    getline(std::cin, linea);
    ss = stringstream(linea);
    ss >> sfirst;
  }
  cout << "---\n";
  return true;
}

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
