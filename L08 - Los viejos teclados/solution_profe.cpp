/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */


/*  
  Solución al problema "Los viejos teclados T9"
  Manuel Montenegro Montes
*/


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


  // Llama a una función auxiliar privada `find_le`. Por tanto, el coste es el
  // de esa llamada (que es O(log N), donde N es el número de elementos del
  // conjunto)
  pair<T, bool> find_le(const T &elem) {
    return find_le(root_node, elem);
  }


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


  // Encuentra el mayor elemento de entre todos los que son menores o iguales
  // que `elem`. Para ello tiene en cuenta los elementos que están por debajo
  // de `root` (incluyendo root).

  // El coste viene dado por la siguiente recurrencia (donde N es el tamaño
  // del árbol)
  // T(0) = k0
  // T(N) = T(N / 2) + k1 si N > 0, suponiendo que el árbol está equilibrado
  //
  // Por tanto, el coste es O(log N), dnode N es el tamaño del árbol que está
  // por debajo de `root`.

  pair<T, bool> find_le(Node *root, const T &elem) {
    // Si el árbol está vacío, no he encontrado el elemento
    if (root == nullptr) {
      return {{}, false};
    } else if (root->elem == elem) {
      // Si el elemento a buscar está en la raíz, lo he encontrado
      return {root->elem, true};
    } else if (root->elem < elem) {
      // Si el elemento a buscar es mayor que la raíz, lo busco en el subárbol
      // derecho.
      auto [x, found] = find_le(root->right, elem);
      if (found) {
        // Si estaba en el subárbol derecho, o había alguno menor que él,
        // devuelvo el mayor de todos los menores que él.
        return {x, true};
      } else {
        // Si todos los elementos del subárbol derecho son mayores que elem,
        // entonces la raíz del árbol es el elemento que estoy buscando.
        return {root->elem, true};
      }
    } else {  // elem < root->elem
      // Si el elemento a buscar es menor que la raíz, lo busco en el hijo
      // izquierdo. Si encuentro allí alguno menor que elem, lo devuelvo; si
      // no, devuelvo false. En resumen, devuelvo lo que me diga la llamada
      // recursiva.
      return find_le(root->left, elem);
    }    
  }

};

template <typename T>
std::ostream &operator<<(std::ostream &out, const SetTree<T> &set) {
  set.display(out);
  return out;
}

// Función para tratar UN caso de prueba. Devuelve true si se ha tratado un
// caso de prueba o false si no lo ha hecho porque se ha encontrado con la
// marca de fin de entrada (0 0)
bool tratar_caso() {
  // El coste es O(N log N + M log N), donde N es el número de teclas del
  // teclado y M es la longitud del mensaje que se quiere escribir.
  // Otras maneras equivalentes de expresar el coste:
  //
  //   O((N + M) log N)
  //   O(max{N, M} * log N)
  //   O(max{N log N, M log N})
 
  int num_teclas, tam_mensaje;
  cin >> num_teclas >> tam_mensaje;

  if (num_teclas == 0 && tam_mensaje == 0) {
    return false;
  }

  SetTree<int> teclas;
  // Coste del bucle (N iteraciones * O(log N) cada iteración => O(N * log N))
  for (int i = 0; i < num_teclas; i++) {    // Leo las teclas del teclado y las inserto en el conjunto
    int x; cin >> x;
    teclas.insert(x); // O(log N)
  }

  int num_pulsaciones = 0; // Número de pulsaciones acumuladas hasta el momento
  bool valido = true;      // Si todos los carácteres son válidos, o se ha encontrado alguno
                           // que no es tecleable.

  // Coste del bucle (M iteraciones * O(log N) cada iteración => O(M * log N))
  for (int i = 0; i < tam_mensaje; i++) {
    int x; cin >> x;
    if (valido) {
      auto [tecla, b] = teclas.find_le(x);  // O(log N)
      if (!b) {
        valido = false;
      } else {
        num_pulsaciones += 1 + (x - tecla);
      }
    }
  }
  if (!valido) {
    cout << "NO SE PUEDE\n";
  } else {
    cout << num_pulsaciones << "\n";
  }

  return true;
}





int main() {
  // Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
  while (tratar_caso()) { }
  return 0;
}
