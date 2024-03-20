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


// Añade los #include que necesites
#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>  // Para la clase pair
#include <tuple>    // Para la clase tuple
#include <queue>
#include <cmath>

using namespace std;

/*
  Implementación de árboles binarios vista en clase
*/

template <class T> class BinTree {
public:
  BinTree() : root_node(nullptr) {}

  BinTree(const T &elem)
      : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

  BinTree(const BinTree &left, const T &elem, const BinTree &right)
      : root_node(std::make_shared<TreeNode>(left.root_node, elem,
                                             right.root_node)) {}

  bool empty() const { return root_node == nullptr; }

  const T &root() const {
    assert(root_node != nullptr);
    return root_node->elem;
  }

  BinTree left() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->left;
    return result;
  }

  BinTree right() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->right;
    return result;
  }

  void display(std::ostream &out) const { display_node(root_node, out); }

private:
  // Las definiciones de TreeNode y NodePointer dependen recursivamente
  // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
  // para que el compilador sepa, cuando analice la definición de NodePointer,
  // que TreeNode va a ser definida más adelante.

  struct TreeNode;
  using NodePointer = std::shared_ptr<TreeNode>;

  struct TreeNode {
    TreeNode(const NodePointer &left, const T &elem, const NodePointer &right)
        : elem(elem), left(left), right(right) {}

    T elem;
    NodePointer left, right;
  };

  NodePointer root_node;

  static void display_node(const NodePointer &root, std::ostream &out) {
    if (root == nullptr) {
      out << ".";
    } else {
      out << "(";
      display_node(root->left, out);
      out << " " << root->elem << " ";
      display_node(root->right, out);
      out << ")";
    }
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const BinTree<T> &tree) {
  tree.display(out);
  return out;
}

template <typename T> BinTree<T> read_tree(std::istream &in) {
  char c;
  in >> c;
  if (c == '.') {
    return BinTree<T>();
  } else {
    assert(c == '(');
    BinTree<T> left = read_tree<T>(in);
    T elem;
    in >> elem;
    BinTree<T> right = read_tree<T>(in);
    in >> c;
    assert(c == ')');
    BinTree<T> result(left, elem, right);
    return result;
  }
}




//@ <answer>
// ----------------------------------------------
// Modificar a partir de aquí
// ----------------------------------------------

// Implementa la función pedida a continuación e indica y justifica su coste.

// Puedes definir las funciones auxiliares que sean necesarias. Para cada una
// de ellas, indica y justifica su coste.
/*
El coste de la funcion num_mellas() es lineal O(n), en el peor de los casos, cuando nos encontramos con un arbol completo sin mellas, siendo n el numero de nodos del arbol, recorridos con bfs.
El bucle que se encuentra dentro del recorrido no modifica el coste solamente sirve de apoyo para que el recorrido de la cola podamos ir diferenciando en que nivel del arbol nos encontramos en cada momento.
El bucle del final solo se encarga de vaciar la cola que contiene los nodos en los que no se va a iterar y hacer operaciones, 
entra dentro del coste del primer bucle while(!pending.empty) que es el que marca el coste de la funcion num_mellas()
El resto de operaciones es de tiempo constante 
*/

template <typename T>
int num_mellas(const BinTree<T> &t) {
  int mellas=0;
  int n=0;
  int i=0;
  bool huboMella=false;
  bool huboMellacompleto=false;
  bool esArbolCompeto=true;
  queue<BinTree<T>> pending;
  pending.push(t);

  while (!pending.empty())
  {
    int numNodos = pending.size();
    if (numNodos == pow(2, i))
    {
      i++;
      while (numNodos > 0)
      {
        BinTree<T> current = pending.front();
        pending.pop();

        if (!current.left().empty() && !current.right().empty())
        { // Hay hijo izq y der
            if(huboMellacompleto){
              mellas++;
              huboMellacompleto=false;
            }
            huboMella=false;
          pending.push(current.left());
          pending.push(current.right());
        }
        else if(current.left().empty() && current.right().empty()){
          if(!huboMella)huboMellacompleto=true;
        }
        else if(!current.left().empty() && current.right().empty()){
          if(huboMellacompleto){
            mellas++;huboMellacompleto=false;
          }
          mellas++;
          huboMella=true;
          esArbolCompeto=false;
        }
        else if(current.left().empty() && !current.right().empty()){
          if(!huboMella||huboMellacompleto)
            mellas++;
          huboMella=false;
          huboMellacompleto=false;
          esArbolCompeto=false;
        }
   
        numNodos--;
      }
    }else{
    esArbolCompeto=false;
    while(!pending.empty()) pending.pop();
    }
  }
  if(huboMellacompleto&&!esArbolCompeto)mellas++;
  return mellas;
}

// ----------------------------------------------
// No modificar a partir de la línea
// ----------------------------------------------
//@ </answer>

// Función para tratar UN caso de prueba.
void tratar_caso() {
  BinTree<char> t = read_tree<char>(cin);
  cout << num_mellas(t) << "\n";
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

  // La entrada comienza con el número de casos de prueba.
  int num_casos;
  cin >> num_casos;

  // Llamamos a `tratar_caso` tantas veces como el número anterior.
  for (int i = 0; i < num_casos; i++) {
    tratar_caso();
  }

  // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
