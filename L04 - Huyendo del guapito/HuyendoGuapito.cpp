/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
  * modificar el c�digo contenido entre las etiquetas <answer>
  * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
  * prohibida, pues no se tendr� en cuenta para la correcci�n.
  *
  * Tampoco esta permitido modificar las l�neas que contienen
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
    vienen implementadas en la biblioteca est�ndar de C++, que son las
    siguientes:

    - queue, definida en el fichero de cabecera <queue>
      Documentaci�n: https://en.cppreference.com/w/cpp/container/queue

    - stack, definida en el fichero de cabecera <stack>
      Documentaci�n: https://en.cppreference.com/w/cpp/container/stack

    - deque, definida en el fichero de cabecera <deque>
      Documentaci�n: https://en.cppreference.com/w/cpp/container/deque

    A�ade los #include con los ficheros de cabecera del TAD o los TADs que
    vais a utilizar, aunque est�n fuera de las etiquetas <answer>...</answer>.
  */


#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 
#include <utility>
#include <queue>

using namespace std;

//@ <answer>
// ----------------------------------------------
// Modificar a partir de aqu�
// ----------------------------------------------


// A�ade los tipos de datos auxiliares y funciones que necesites

/*El coste solucion() es de O(N*T) en el caso peor, siendo N el numero de horas disponibles en un dia  y T el numero de dias en los cuales
se realizan pruebas
El coste de todas las operaciones del interior del while son de coste constante O(1). */
int solucion(queue<char>p, queue<pair<char, int>>a, int& hdisp) {
    while (hdisp != 0 && !a.empty()) { 
        if (p.front() == 'G') { // Supende siempre
            a.front().second++; // Se presenta otra vez
            a.push(a.front());
            a.pop();
        }
        else if (p.front() == 'A') { // Suspende dependiendo B/M
            if (a.front().first == 'B') { // Aprueba
                a.pop();
            }
            else {
                a.front().second++; // Se presenta otra vez
                a.push(a.front());
                a.pop();
            }
        }
        else if (p.front() == 'B') { // Suspende dependiendo B/M y 3 veces apruebas siempre   
            if (a.front().first == 'B') { // Aprueba
                a.pop();
            }
            else {
                if (a.front().second >= 2) { // Aprueba a la 3�
                    a.pop();
                }
                else {
                    a.front().second++; // Se presenta otra vez
                    a.push(a.front());
                    a.pop();
                }
            }
        }
        p.push(p.front());
        p.pop();
        hdisp--;
    }

    return a.size();
}


// Implementa aqu� la funci�n para tratar UN caso de prueba. La funci�n
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de fichero. Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la funci�n.

bool tratar_caso() {
    int N, M, T;
    queue<char> p; // Cola para profesores, O(1)
    queue<pair<char, int>> a; // Cola para alumnos, O(1)
    //p.clear();
    //a.clear();
    cin >> N >> M >> T;

    if (!cin)
        return false;

    char c;
    int hdisp = N * T;
    for (int i = 0; i < N; i++) {
        cin >> c;
        p.push(c); // O(1)
    }

    char alumno;
    for (int i = 0; i < M; i++) {
        cin >> alumno;
        a.push({ alumno,0 }); // O(1)
    }

    cout << solucion(p, a, hdisp) << endl;

    return true;
}

// ----------------------------------------------
// No modificar a partir de la l�nea
// ----------------------------------------------
//@ </answer>

int main() {
    // Si est�s ejecutando el programa en tu ordenador, las siguientes l�neas
    // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
    // �til para no tener que teclear los casos de prueba por teclado cada vez
    // que ejecutas el programa.
    //
    // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
    // comenta las l�neas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Ejecutamos tratar_caso() hasta que nos devuelva `false`
    while (tratar_caso()) {}

    // Comenta esto tambi�n si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
