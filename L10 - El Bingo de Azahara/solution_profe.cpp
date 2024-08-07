/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */


/*
  El bingo de Azahara

  Manuel Montenegro
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

bool tratar_caso() {
  int num_jugadores;
  cin >> num_jugadores;

  if (num_jugadores == 0) return false;

  // Para cada jugador, almacenamos la cantidad de números que le quedan sin tachar
  unordered_map<string, int> contadores;
  // Para cada número, almacenamos los nombres de jugadores que tienen ese número
  unordered_map<int, vector<string>> numeros;

  // --------------------------------------------------------------------
  // Primera parte: leemos los cartones de la entrada
  // --------------------------------------------------------------------
  for (int i = 0; i < num_jugadores; i++) {
    string nombre;
    cin >> nombre;

    int numero;
    cin >> numero;

    while (numero != 0) {
      numeros[numero].push_back(nombre);
      contadores[nombre]++;
      cin >> numero;
    }
  }
  // Coste: Suponemos que:
  //    - N es el número de jugadores
  //    - T[i] es la cantidad de números que tiene el jugador i-ésimo.
  //    - T es la suma de las cantidades de números que tienen todos los jugadores
  //        es decir, Σ({ T[i] | 0 <= i < N })
  //
  // El coste de leer el cartón es O(N + T)
  // --------------------------------------------------------------------


  // --------------------------------------------------------------------
  // Segunda parte: leemos las bolas que salen del bombo y simulamos
  //                el bingo
  // --------------------------------------------------------------------

  set<string> bingo;  // Aquí almacenaremos los ganadores

  while (bingo.empty()) { // Mientras no haya ganadores
    int bola;
    cin >> bola;  // Sacamos siguiente bola

    for (const string &s: numeros[bola]) {  // Para todos los jugadores que tienen esa bola
      contadores[s]--;  // Decrementamos el contador de ese jugador
      if (contadores[s] == 0) { // Si a ese jugador no le quedan números sin tachar, canta bingo
        bingo.insert(s);
      }
    }
  }
  // Coste: Suponemos que:
  //  - L es el número de bolas que han salido del bombo
  //  - M[i] es el número de jugadores que tienen la bola i-ésima
  //  - G es el número de ganadores.
  //
  // El bucle interno hace M[bola] iteraciones, y el bucle externo L iteraciones.
  // El bucle interno, en total, hace Σ{M[i] | `i` sale del bombo} iteraciones, pero 
  // como solo recorremos los jugadores que tienen la bola i-ésima, se tiene que
  // Σ{M[i] | `i` sale del bombo} <= T, donde T se define como antes: la cantidad total
  // de números que hay en todos los cartones.
  // Dentro del bucle hay una llamada a `insert()`, pero esta llamada solamente se hace
  // en la última iteración del bucle externo.
  // El coste de esta segunda parte es O(L + T + G log G)
  // --------------------------------------------------------------------



  // --------------------------------------------------------------------
  // Tercera parte: imprimimos los ganadores
  // --------------------------------------------------------------------
  auto it = bingo.begin();
  cout << *it;  // Imprimimos el primer ganador
  it++;

  // Y a continuación los siguientes, cada uno precedido por un espacio
  while (it != bingo.end()) {
    cout << " " << *it;
    it++;
  }

  cout << "\n";
  // Coste: O(G), donde G es el número de ganadores
  // --------------------------------------------------------------------


  // Coste total: O(N + L + T + G log G)
  return true;
}

int main() {
  while (tratar_caso()) {  }

  return 0;
}
