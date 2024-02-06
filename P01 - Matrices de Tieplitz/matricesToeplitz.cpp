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
    
    assert(m>=1&&n>=1);
    matriz.resize(n,vector<int>(m,v)); // Resize modifica el tamanio del vector n y de m (lo hemos dado en PCOM)
  }
  int get(int i , int j){
    return matriz[i][j];
  }
  void set(int i, int j, int v){
     matriz[i][j]=v;
  }
  private:
  vector<int>diagonales;
};
// No te olvides de indicar y justificar el coste del constructor y el coste de cada método.
/*El coste del constructor es de O(n^2) Siendo n el numero total de elementos de la matriz de tamanio n, m
Siendo n en numero de filas y m en numero de columnas
Coste get: O(1)
Coste set: O(1)

Lo hemos hecho de manera que sale mal la solucion porque nuestro setter mete el valor en el vector y debemos
cambiar la diagonal completa, no nos da tiempo a cambiarlo
*/

bool tratar_caso() {
  // Implementa el código para tratar un caso de prueba.
  int n,m,v;
  cin>>n>>m>>v;
  if(n==m==v==0)return false;
  ToeplitzMatrix matriz(n,m,v);
  // Esta función debe devolver `false` si, en lugar de un caso de prueba,
  // se ha encontrado con la marca de fin de entrada (0 0 0).
  string cadena;
  int f,c,val;
  cin>>cadena;
  while(cadena!="FIN"){
    if(cadena=="set"){
      cin>>f>>c>>val;
      matriz.set(f,c,val);
    }else if(cadena=="get"){
      cout<<matriz.get(f,c)<<endl;
    }
    cin>> cadena;
  }
  cout<<"---\n";
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
