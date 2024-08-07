/* ----------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ----------------------------------------------------
 *   Examen final. Convocatoria ordinaria (mayo 2024)
 *                   Ejercicio 1      
 * ----------------------------------------------------
 */


/*
 * Solución por Manuel Montenegro Montes
 */


#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cctype>
#include <stack>

using namespace std;


/*
  Recorremos la lista `lineas` de izquierda a derecha. Guardamos en una pila
  los niveles de indentación de los bloques que están abiertos. Cada vez que
  encontramos una llave de apertura, apilamos el nivel de indentación de esa
  llave en la pila. Cada vez que encontramos una llave de cierre, desapilamos
  el último nivel de indentación.

  Cada vez que encontramos una llave de cierre o una línea que no es ni
  apertura ni cierre, hemos de mirar si su nivel de indentación coincide con
  el del bloque actual, que está en la cima de la pila.

  El coste de la función `comprueba_indentacion` es O(N), donde N es el tamaño
  de la lista `lineas`. Tenemos un bucle con tantas iteraciones como
  elementos tiene la lista de entrada. Dentro de cada iteración, todas las
  operaciones tienen coste amortizado O(1).
 */

int comprueba_indentacion(const list<pair<int, char>> lineas) {
  int contador_lineas = 1;  // Número de línea actual
  int linea_fallo = -1;     // Número de línea donde se encuentra el primer fallo
  auto it = lineas.begin();

  stack<int> niveles;       // Pila con los niveles de indentación de los
                            // bloques abiertos hasta el momento.

  // Comenzamos en el nivel de indentación 0
  niveles.push(0);  

  while (linea_fallo == -1 && it != lineas.end()) {
    auto [indent, ch] = *it;

    if (ch == '{') {      
      // Si la llave de apertura no está más a la derecha del nivel
      // de indentación actual, no está bien indentada. De lo contrario
      // almacenamos el nivel de indentación de la llave en la pila.
      if (!(indent > niveles.top())) {
        linea_fallo = contador_lineas;
      } else {
        niveles.push(indent);
      }
    } else {
      // Si no es llave de apertura, comprobamos que está en el nivel
      // de indentación adecuado
      if (indent != niveles.top()) {
        linea_fallo = contador_lineas;
      }

      // Además, si es una llave de cierre, desapilamos el nivel de
      // indentación actual, porque hemos terminado un bloque.
      if (ch == '}') {
        niveles.pop();
      }
    }
    contador_lineas++;
    it++;
  }

  return linea_fallo;
}


// Función para tratar un caso de prueba
bool tratar_caso() {
  // Cada caso comienza con el número de líneas del programa
  int num_lineas;
  cin >> num_lineas;

  // Si hay cero líneas, terminamos
  if (num_lineas == 0) return false;

  // Tras leer el número, pasamos a la siguiente línea, que va
  // a ser la línea 1 del programa.
  cin.ignore(10, '\n');

  list<pair<int, char>> lineas;

  for (int i = 0; i < num_lineas; i++) {
    // Para cada línea, la leemos de la entrada
    string l;
    getline(cin, l);

    // Contamos los espacios que hay antes del primer carácter no blanco
    int indent = 0;
    while (isspace(l[indent])) {
      indent++;
    }

    // Insertamos el par correspondiente en `lineas`
    lineas.push_back({indent, l[indent]});
  }

  // Llamamos a la función pedida
  int result = comprueba_indentacion(lineas);

  // Imprimimos el resultado
  if (result == -1) {
    cout << "CORRECTO\n";
  } else {
    cout << result << "\n";
  }

  return true;
}

int main() {
  // Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
  while (tratar_caso()) { }
  return 0;
}
