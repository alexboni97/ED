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
  Componente 1: ALEX GUILLERMO BONILL TACO
  Componente 2: BRYAN EDUARDO CORDOVA ASCURRRA
*/
//@ </answer>


// Añade los #include que necesites
#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

/*
  Implementación de conjuntos. Contiene la definición del método `find_le` que
  tendrás que implementar.
*/

template <typename T> class SetTree {
public:
  SetTree() : root_node(nullptr), num_elems(0) {}
  SetTree(const SetTree &other)
      : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) {}
  ~SetTree() { delete_nodes(root_node); }

  void insert(const T &elem) {
    auto [new_root, inserted] = insert(root_node, elem);
    root_node = new_root;
    if (inserted) {
      num_elems++;
    }
  }

  bool contains(const T &elem) const { return search(root_node, elem); }

  void erase(const T &elem) {
    auto [new_root, removed] = erase(root_node, elem);
    root_node = new_root;
    if (removed) {
      num_elems--;
    }
  }

  int size() const { return num_elems; }
  bool empty() const { return num_elems == 0; }

  SetTree &operator=(const SetTree &other) {
    if (this != &other) {
      num_elems = other.num_elems;
      delete_nodes(root_node);
      root_node = copy_nodes(other.root_node);
    }
    return *this;
  }

  void display(std::ostream &out) const {
    out << "{";
    display(root_node, out);
    out << "}";
  }


//@ <answer>
  // Implementa aquí la función `find_le` que se pide.
  // Si necesitas métodos privados auxiliares, impleméntalos al final de la clase

  // ¡No olvides el coste! Para ello puedes suponer que el árbol binario de
  //  búsqueda está equilibrado
  pair<T, bool> find_le(const T &elem) {
    auto p=search_le(this->root_node,elem);
    return p;
  }
//@ </answer>


private:
  struct Node {
    T elem;
    Node *left, *right;

    Node(Node *left, const T &elem, Node *right)
        : left(left), elem(elem), right(right) {}
  };

  Node *root_node;
  int num_elems;

  static Node *copy_nodes(const Node *node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new Node(copy_nodes(node->left), node->elem,
                      copy_nodes(node->right));
    }
  }

  static void delete_nodes(const Node *node) {
    if (node != nullptr) {
      delete_nodes(node->left);
      delete_nodes(node->right);
      delete node;
    }
  }

  static std::pair<Node *, bool> insert(Node *root, const T &elem) {
    if (root == nullptr) {
      return {new Node(nullptr, elem, nullptr), true};
    } else if (elem < root->elem) {
      auto [new_root_left, inserted] = insert(root->left, elem);
      root->left = new_root_left;
      return {root, inserted};
    } else if (root->elem < elem) {
      auto [new_root_right, inserted] = insert(root->right, elem);
      root->right = new_root_right;
      return {root, inserted};
    } else {
      return {root, false};
    }
  }

  static bool search(const Node *root, const T &elem) {
    if (root == nullptr) {
      return false;
    } else if (elem == root->elem) {
      return true;
    } else if (elem < root->elem) {
      return search(root->left, elem);
    } else {
      return search(root->right, elem);
    }
  }

  static std::pair<Node *, bool> erase(Node *root, const T &elem) {
    if (root == nullptr) {
      return {root, false};
    } else if (elem < root->elem) {
      auto [new_root_left, erased] = erase(root->left, elem);
      root->left = new_root_left;
      return {root, erased};
    } else if (root->elem < elem) {
      auto [new_root_right, erased] = erase(root->right, elem);
      root->right = new_root_right;
      return {root, erased};
    } else {
      return {remove_root(root), true};
    }
  }

  static Node *remove_root(Node *root) {
    Node *left_child = root->left, *right_child = root->right;
    delete root;
    if (left_child == nullptr && right_child == nullptr) {
      return nullptr;
    } else if (left_child == nullptr) {
      return right_child;
    } else if (right_child == nullptr) {
      return left_child;
    } else {
      auto [lowest, new_right_root] = remove_lowest(right_child);
      lowest->left = left_child;
      lowest->right = new_right_root;
      return lowest;
    }
  }

  static std::pair<Node *, Node *> remove_lowest(Node *root) {
    assert(root != nullptr);
    if (root->left == nullptr) {
      return {root, root->right};
    } else {
      auto [removed_node, new_root_left] = remove_lowest(root->left);
      root->left = new_root_left;
      return {removed_node, root};
    }
  }

  static void display(Node *root, std::ostream &out) {
    if (root != nullptr) {
      if (root->left != nullptr) {
        display(root->left, out);
        out << ", ";
      }
      out << root->elem;
      if (root->right != nullptr) {
        out << ", ";
        display(root->right, out);
      }
    }
  }


//@ <answer>

  // Implementa aquí las funciones privadas auxiliares que necesites.

  // ¡No olvides el coste! Para ello puedes suponer que el árbol binario de
  //  búsqueda está equilibrado
  // Suponiendo que el arbol es un ABB equilibrado el coste en el caso peor es O(log n)
  // siendo n el num de nodos del arbol al que hace referencia la raiz root pasada por parametro 
  static std::pair<T, bool> search_le(Node *root, const T &elem)  {
    if (root == nullptr){
      return {0, false};
    }else if (root->elem < elem){
      auto [value, encontrado] = search_le(root->right, elem);
      if (!encontrado)
        return {root->elem, true};
      else
        return {value, encontrado};
    }else if (root->elem > elem){
      auto [value, encontrado] = search_le(root->left, elem);
      return {value, encontrado};
    }else
      return {elem, true};
  }

//@ </answer>
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const SetTree<T> &set) {
  set.display(out);
  return out;
}

//@ <answer>
// ----------------------------------------------
// Modificar a partir de aquí
// ----------------------------------------------



// Función para tratar UN caso de prueba. Devuelve true si se ha tratado un
// caso de prueba o false si no lo ha hecho porque se ha encontrado con la
// marca de fin de entrada (0 0)
bool tratar_caso(){
  int N, M;
  cin >> N >> M;

  if (N == 0 && M == 0)  {
    return false;
  }
  // Indica el coste de tratar un caso de prueba. Para ello puedes suponer que
  // los conjuntos que utilices están representados mediante árboles de
  // búsqueda equilibrados.
  SetTree<int> t;
  stack<int> pila;
  int elem;

  for (int i = 0; i < N; i++){
    cin >> elem;
    t.insert(elem);
  }

  for (int i = 0; i < M; i++){
    cin >> elem;
    pila.push(elem);
  }
  pair<int, bool> sol;
  sol.first = 0;
  sol.second = true;
  while (!pila.empty()){
    auto solElem = t.find_le(pila.top());
    if (solElem.second == false){
      sol.second = false;
      break;
    }
    else
      sol.first = sol.first - solElem.first + pila.top() + 1;
    pila.pop();
  }

  if (sol.second == false)
    cout << "NO SE PUEDE" << endl;
  else
    cout << sol.first << endl;

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

  // Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
  while (tratar_caso()) { }

  // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
