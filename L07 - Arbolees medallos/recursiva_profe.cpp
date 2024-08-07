/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

// Solución recursiva
// Autor: Manuel Montenegro Montes

#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>  // Para la clase pair
#include <tuple>    // Para la clase tuple

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







// La función numero_mellas_aux devuelve una tupla de cuatro componentes:
// - Primera componente: número de mellas en el árbol
// - Segunda componente: si tenemos mella por la izquierda
// - Tercera componente: si tenemos mella por la derecha
// - Cuarta componente: altura del árbol
//
// Ver explicación en: https://drive.google.com/file/d/1KyPDGvlSyMY9XhIpYh19hFMMXnISTNru/view

// El coste viene dado por la recurrencia, donde n denota el número de nodos del árbol.
//
// T(0) = k_1
// T(n) = T(n_i) + T(n_d) + k_2 para n > 0
//
// donde k_1 y k_2 son constantes, n_i es el número de nodos del hijo izquierdo y n_d
// es el número de nodos del hijo derecho. Se cumple que n = n_i + n_d + 1.
//
// Esta recurrencia tiene coste O(n), independientemente de si el árbol es equilibrado o no.
template <typename T>
tuple<int, bool, bool, int> numero_mellas_aux(const BinTree<T> &t) {
  if (t.empty()) {
    // Si el árbol es vacío, consideramos que es una mella, porque es hijo
    // de un padre.
    return {1, true, true, 0};
  } else if (t.left().empty() && t.right().empty()) {
    // Si es una hoja, consideramos que no tiene mellas
    return {0, false, false, 1};
  } else {
    // Hacemos las llamadas recursivas.
    auto [num_mellas_iz, mella_iz_iz, mella_iz_dr, alt_iz] = numero_mellas_aux(t.left());
    auto [num_mellas_dr, mella_dr_iz, mella_dr_dr, alt_dr] = numero_mellas_aux(t.right());

    // Si un hijo tiene una altura menos que el otro, hemos de ajustar su resultado,
    // ya que el hijo más corto en realidad tiene una mella, que entra en contacto
    // con ambos bordes.

    if (alt_iz < alt_dr) {
      mella_iz_iz = mella_iz_dr = true;
      num_mellas_iz = 1;
    } else if (alt_dr < alt_iz) {
      mella_dr_iz = mella_dr_dr = true;
      num_mellas_dr = 1;
    }

    // En principio el número de mellas es la suma de ambos hijos.
    int num_mellas = num_mellas_iz + num_mellas_dr;

    // Pero si una de las mellas del hijo izquierdo está en el borde derecho, y
    // una de las mellas del hijo derecho está en el borde izquierdo, ambas forman
    // una única mella que hemos contabilizado dos veces (una por cada llamada recursiva),
    // por lo que hemos de decrementar en uno el número de mellas contadas.
    if (mella_iz_dr && mella_dr_iz) num_mellas--;

    int altura = 1 + max(alt_iz, alt_dr);

    return {num_mellas, mella_iz_iz, mella_dr_dr, altura};
  }
}


// El coste de esta función es lineal con respecto al número de nodos
// del árbol pasado como parámetro, ya que realiza una llamada a `num_mellas_aux`
// que tiene ese mismo coste.
template <typename T>
int num_mellas(const BinTree<T> &t) {
  auto [num, _iz, _dr, _alt] = num_mellas_aux(t);
  return num;
}


// Función para tratar UN caso de prueba.
void tratar_caso() {
  BinTree<char> t = read_tree<char>(cin);
  cout << num_mellas(t) << "\n";
}


int main() {
  // La entrada comienza con el número de casos de prueba.
  int num_casos;
  cin >> num_casos;

  // Llamamos a `tratar_caso` tantas veces como el número anterior.
  for (int i = 0; i < num_casos; i++) {
    tratar_caso();
  }

  return 0;
}
