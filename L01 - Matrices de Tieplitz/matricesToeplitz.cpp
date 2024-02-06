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
  Componente 1: ALEX GUILLERMO BONILLA TACO
  Componente 2: BRYAN EDUARDO CORDOVA ASCURRA
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>


using namespace std;

// Define aquí la clase ToeplitzMatrix e implementa sus métodos.
class ToeplitzMatrix{
public:
  ToeplitzMatrix(int n,int m,int v){
    assert(m >= 1 && n >= 1);
    this->n = n;
    diagonales = vector<int>(n + m - 1, v);
  }
  int get(int i , int j)const{
    return diagonales[j + n - 1 - i];
  } 
  void set(int i, int j, int v){
    diagonales[j + n - 1 - i] = v;
  }
  private:
  vector<int>diagonales;
  int n;
};
// No te olvides de indicar y justificar el coste del constructor y el coste de cada método.
/*El coste del constructor es de O(n+m-1) Siendo n+m-1 el numero total de elementos del vector de diagonales que se ha inicializado a v.
Siendo n en numero de filas y m en numero de columnas y v el valor de todos los elementos de la matriz al inicio.
Coste metodo get: O(1) cte
Coste metodo set: O(1) cte

*/

bool tratar_caso() {
  // Implementa el código para tratar un caso de prueba.
  int n, m, v;
  cin >> n >> m >> v;
  if (n == 0 && m == 0 && v == 0)
    return false;
  ToeplitzMatrix matriz(n, m, v);
  // Esta función debe devolver `false` si, en lugar de un caso de prueba,
  // se ha encontrado con la marca de fin de entrada (0 0 0).
  string cadena;
  int f, c, val;
  cin >> cadena;
  while (cadena != "FIN"){
    if (cadena == "set"){
      cin >> f >> c >> val;
      matriz.set(f, c, val);
    }
    else if (cadena == "get"){
      cin >> f >> c ;
      cout << matriz.get(f, c) << endl;
    }
    cin >> cadena;
  }
  cout << "---\n";
  // En caso contrario, debe procesar el caso de prueba y devolver `true`.
  return true;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
