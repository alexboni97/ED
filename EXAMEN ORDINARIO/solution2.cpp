/* ----------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ----------------------------------------------------
 *   Examen final. Convocatoria ordinaria (mayo 2024)
 *                   Ejercicio 2      
 * ----------------------------------------------------
 */

/*
 * Solución por Manuel Montenegro Montes
 */


#include <iostream>
#include <fstream>
#include <utility>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>


// Implementación de árboles binarios vista en clase.
// No se permite modificar esta clase.

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


using namespace std;

/*
 Este problema es similar al problema del diámetro de un árbol visto en clase.
 Necesitamos una función auxiliar que nos devuelva la ruta de mayor interés
 que acabe en la raíz del árbol.
*/


// Devuelve un par:
//  - Primera componente: valoración máxima obtenible con cualquier ruta que
//    empiece y termine en un parador.
//  - Segunda componente: valoración máxima obtenible con cualquier ruta que
//    empiece en un parador y termine en la raíz del árbol

// El coste viene dado por la siguiente recurrencia, donde n denota el número
// de nodos del árbol.
//
// T(0) = k_1
// T(n) = T(n_i) + T(n_d) + k_2  (si n > 0)
//
// Donde n_i es el número de nodos del hijo izquierdo, y n_d es el número de
// nodos del hijo derecho, cumpliéndose que n = n_i + n_d + 1.
// Independientemente de si el árbol está equilibrado o no, esta recurrencia
// representa un coste O(n), donde n es el número de nodos del árbol.

pair<int, int> max_interes_ruta_aux(const BinTree<int> &montanya) {
  if (montanya.empty()) {
    // Si la montaña solo consiste en un parador, no encontramos
    // nada de valor.
    return {0, 0};
  } else {
    auto [max_iz, ruta_raiz_iz] = max_interes_ruta_aux(montanya.left());
    auto [max_dr, ruta_raiz_dr] = max_interes_ruta_aux(montanya.right());

    // Para calcular la mejor ruta que acaba en la raíz del árbol, se comparan
    // las rutas que llevan a las raíces de los subárboles y nos quedamos con
    // la mejor de ellas, añadiéndole el valor de la raiz
    int max_camino_raiz = max(ruta_raiz_iz, ruta_raiz_dr) + montanya.root();

    // La mejor ruta que empieza y acaba en parador encaja en uno de los
    // siguientes casos:
    //  - Está contenida enteramente en el hijo izquierdo. En ese caso, su valor
    //    es max_iz.
    //  - Está contenida enteramente en el hijo derecho. En ese caso, su valor
    //    es max_dr.
    //  - Recorre ambos hijos, pasando por la raíz. En ese caso, su valor es
    //    ruta_raiz_iz + montanya.root() + ruta_raiz_dr.
    //
    //  Nos quedamos con el máximo de esas tres posibilidades.

    int max_camino = max(max(max_iz, max_dr), ruta_raiz_iz + montanya.root() + ruta_raiz_dr);
    return {max_camino, max_camino_raiz};
  }
}


// Coste O(n), donde n es el número de nodos del árbol pasado como parámetro,
// porque se llama a max_interes_ruta_aux, que tiene ese mismo coste.
int max_interes_ruta(const BinTree<int> &montanya) {
  return max_interes_ruta_aux(montanya).first;
}


// Función para tratar un caso de prueba

bool tratar_caso() {
  BinTree<int> arbol = read_tree<int>(cin);
  if (arbol.empty()) return false;
  cout << max_interes_ruta(arbol) << "\n";
  return true;
}

int main() {  
  // Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
  while (tratar_caso()) { }
  return 0;
}
