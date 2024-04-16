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

#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <set>

// Añade los include que necesites

using namespace std;
pair<bool,set<string>>comprobarSiHayGanadores(unordered_map<string, unordered_set<int>>jugadores, int num){
    pair<bool,set<string>> ganadores;
    for(pair<string,unordered_set<int>>j:jugadores){
        auto itj=j.second.find(num);
        j.second.erase(itj);
        if(j.second.empty()){
            ganadores.first=true;
            ganadores.second.insert(j.first);
        }
    }
    return ganadores;
}
bool tratar_caso() {
  // Escribe aquí el código para tratar un caso de prueba
    int n;
    cin>>n;
    if(n==0) return false;

    bool esBingo=false;
    string nombre;
    int aux;
    unordered_map<string, unordered_set<int>> jugadores;
    for (int i = 0; i < n; i++) {
        cin>> nombre;
        cin>>aux;
        unordered_set<int> carton;
        while (aux != 0) {
            carton.insert(aux);
            cin>>aux;
        }
        jugadores.insert_or_assign(nombre,carton);
    }
    
    int num;
    pair<bool,set<string>>ganadores;
    while(!esBingo){
        cin>>num;
        ganadores=comprobarSiHayGanadores(jugadores,num);
        if (ganadores.first) {
            esBingo=true;
        }
    }
    set<string> nombres=ganadores.second;
    for(string n:nombres){
        cout << n <<" ";
    }
    cout<<endl;
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
  
  while (tratar_caso()) {  }

  // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
