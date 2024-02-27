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

/*
  En este ejercicio solamente pueden utilizarse las colecciones vistas durante
  esta semana: pilas, colas, o dobles colas.

  En lugar de utilizar las implemtaciones vistas en clase, utilizad las que
  vienen implementadas en la biblioteca estándar de C++, que son las
  siguientes:

  - queue, definida en el fichero de cabecera <queue>
    Documentación: https://en.cppreference.com/w/cpp/container/queue

  - stack, definida en el fichero de cabecera <stack>
    Documentación: https://en.cppreference.com/w/cpp/container/stack

  - deque, definida en el fichero de cabecera <deque>
    Documentación: https://en.cppreference.com/w/cpp/container/deque

  Añade los #include con los ficheros de cabecera del TAD o los TADs que
  vais a utilizar, aunque estén fuera de las etiquetas <answer>...</answer>.
*/


#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 
#include <utility>
#include <deque>

using namespace std;

//@ <answer>
// ----------------------------------------------
// Modificar a partir de aquí
// ----------------------------------------------


// Añade los tipos de datos auxiliares y funciones que necesites


int solucion(deque<char>p, deque<pair<char,int>>a, int &hdisp) {
  while (hdisp != 0 && !a.empty()) {
    if (p.front() == 'G') { // Supende siempre
      a.front().second++; // Se presenta otra vez
      a.push_back(a.front());
      a.pop_front();  
    }
    else if (p.front() == 'A') { // Suspende dependiendo B/M
      if (a.front().first == 'B') { // Aprueba
        a.pop_front();
      }
      else {
        a.front().second++; // Se presenta otra vez
        a.push_back(a.front());
        a.pop_front();
      }
    }
    else if (p.front() == 'B') { // Suspende dependiendo B/M y 3 veces apruebas siempre   
      if (a.front().first == 'B') { // Aprueba
        a.pop_front();
      }
      else {
        if(a.front().second >= 2){ // Aprueba a la 3º
          a.pop_front();
        }
        else {
        a.front().second++; // Se presenta otra vez
        a.push_back(a.front());
        a.pop_front();
        }
      }
    }
    p.push_back(p.front());
    p.pop_front();
    hdisp--;
  }
  
  return a.size();
}


// Implementa aquí la función para tratar UN caso de prueba. La función
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de fichero. Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la función.

bool tratar_caso() {
  int N,M,T;
  deque<char> p;
  deque<pair<char, int>> a;
  p.clear();
  a.clear();
  cin >> N >> M >> T;
  
  if(!cin)
    return false;
  
  char c;
  int hdisp=N*T;
  for(int i=0;i<N;i++){
    cin>>c;
    p.push_back(c);
  }
  
  char alumno;
  for(int i=0; i < M; i++){
    cin>>alumno;
    a.push_back({alumno,0});
  }

  cout<< solucion(p, a, hdisp)<<endl;

  return true;
}

// ----------------------------------------------
// No modificar a partir de la línea
// ----------------------------------------------
//@ </answer>

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

  // Ejecutamos tratar_caso() hasta que nos devuelva `false`
  while (tratar_caso()) { }

  // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
