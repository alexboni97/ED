/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*  
  Solución a la práctica L04 - Huyendo del "guapito"
*/


#include <iostream>
#include <fstream>
#include <cassert>
#include <queue>


using namespace std;


// Tenemos tres examinadores
enum class Examinador { ElGuapito, Agapita, Benito };

// Para representar a cada candidato
struct Candidato {
  bool bueno;   // si conduce bien o mal
  int num_vez;  // número de intento
};

// Sobrecargamos el operador >> para leer un examinador de la entrada
istream &operator>>(istream &in, Examinador &ex) {
  char c;
  in >> c;
  switch (c) {
  case 'G':
    ex = Examinador::ElGuapito;
    break;
  case 'A':
    ex = Examinador::Agapita;
    break;
  case 'B':
    ex = Examinador::Benito;
    break;
  }
  return in;
}

// Sobrecargamos el operador >> para leer un candidato de la entrada
istream &operator>>(istream &in, Candidato &cand) {
  char c;
  in >> c;
  switch (c) {
  case 'B':
    cand.bueno = true;
    break;
  case 'M':
    cand.bueno = false;
    break;
  }
  return in;
}



// Coste O(N + M + N*T), donde N es el número de examinadores (o huecos disponibles cada día)
//                             M es el número de candidatos
//                             T es el número de días
//
// simplificando: O(N + M + N*T) = O(max{N, M, N*T}) = O(max{M, N*T}) o también O(M + N*T)
//
// El primer bucle tiene coste O(N), el segundo O(M) y el tercero O(N*T)
bool tratar_caso() {
  int N, M, T;
  cin >> N >> M >> T;
  // Pasamos a la siguiente línea
  cin.ignore(10, '\n');

  if (cin.eof()) {
    return false;
  }

  // Cola de examinadores y de candidatos
  queue<Examinador> examinadores;
  queue<Candidato> candidatos;

  // Leemos los examinadores de la entrada
  for (int i = 0; i < N; i++) { // N iteraciones * O(1) cada iteración ==> O(N)
    Examinador e;
    cin >> e;
    examinadores.push(e);
  }
  cin.ignore(10, '\n'); // Pasamos a la siguiente línea. Si no, cin >> ch lee el carácter '\n'

  for (int i = 0; i < M; i++) { // M iteraciones * O(1) ==> O(M)
    Candidato c;
    cin >> c;
    c.num_vez = 1;
    candidatos.push(c);
  }
  cin.ignore(10, '\n');

  // Tenemos que repetir el siguiente bucle como máximo N*T veces
  int num_examenes = 0;
  int candidatos_restantes = M;

  // Mientras no hayamos terminado la simulación y todavía queden candidatos
  while (num_examenes < N * T && candidatos_restantes > 0) {  // N * T iteraciones en el caso peor * O(1) ==> O(N * T)
    // Sacamos el examinador y el candidato que tienen el turno
    Examinador e = examinadores.front();
    Candidato c = candidatos.front();
    examinadores.pop();
    candidatos.pop();


    bool aprueba; // Si el candidato aprobará o no

    switch (e) {
    case Examinador::ElGuapito:
      aprueba = false;  // Con el guapito nunca se aprueba
      break;
    case Examinador::Agapita:
      aprueba = c.bueno; // Con Agapita depende de lo bueno que sea el candidato
      break;
    case Examinador::Benito:
      aprueba = c.bueno || c.num_vez >= 3;
                 // Con Benito depende de lo bueno que sea el candidato o de si es su 3ª vez (o posterior)
      break;
    }

    // El examinador vuelve a la cola
    examinadores.push(e);

    // Si el candidato aprueba, lo metemos en la cola incrementando
    // su contador. Si no, no lo metemos y decrementamos el número
    // de candidatos restantes
    if (!aprueba) {
      c.num_vez++;
      candidatos.push(c);
    } else {
      candidatos_restantes--;
    }

    num_examenes++;
  }

  cout << candidatos_restantes << endl;

  return true;
}



int main() {
  // Ejecutamos tratar_caso() hasta que nos devuelva `false`
  while (tratar_caso()) { }
  return 0;
}
