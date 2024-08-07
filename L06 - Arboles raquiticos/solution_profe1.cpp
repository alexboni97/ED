/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*
  Práctica L06 - Árboles raquíticos
  Manuel Montenegro

  Solución que se basa en el hecho de que un árbol es raquítico si y solo si
  es vacío, o bien una hoja, o bien la diferencia entre las alturas de sus hijos
  es exactamente igual a 1.

  Esto se explica aquí:

  https://docs.google.com/document/d/1pB5E3yAVa-EfPuVzkf_3Yuoe6JLIp7mGO6yLhJLETps/edit?usp=drive_link
 */  


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




// Primera componente: si es equilibrado o no
// Segunda componente: si es raquítico o no
// Tercera componente: altura

template <typename T>
tuple<bool, bool, int> analizar(const BinTree<T> &t) {
  if (t.empty()) {
    // El árbol vacío es raquítico
    return { true, true, 0 };
  } else if (t.left().empty() && t.right().empty()) {
    // Una hoja es raquítica

    // Hay que distinguir el caso de las hojas, porque una hoja
    // es raquítica, pero no cumple abs(altura_hi - altura_hd) == 1
    return { true, true, 1 };
  } else {
    // Caso general
    auto [eq_iz, raq_iz, alt_iz] = analizar(t.left());
    auto [eq_dr, raq_dr, alt_dr] = analizar(t.right());
    // Calculamos la altura del árbol entero
    int alt = 1 + max(alt_iz, alt_dr);
    // El árbol entero es equilibrado si y solo si ambos hijos lo son,
    // y si la diferencia entre sus alturas es, como mucho, 1
    bool eq = eq_iz && eq_dr && abs(alt_iz - alt_dr) <= 1;
    // El árbol entero es raquítico si y solo si ambos hijos lo son,
    // y si la diferencia entre sus alturas es exactamente 1
    bool raq = raq_iz && raq_dr && abs(alt_iz - alt_dr) == 1;

    return {eq, raq, alt};
  }
}

/*
 Coste de la función `analizar`.

 Si n es el número de nodos del árbol pasado como parámetro. El coste T(n) en
 tiempo de la función se expresa mediante la siguiente recurrencia.

  T(0) = k1
  T(1) = k2
  T(n) = T(ni) + T(nd) + k3  (si n > 1)

  donde k1, k2 y k3 son constantes, y ni y nd son el número de nodos del hijo
  izquierdo y derecho, respectivamente, sabiendo que ni + nd + 1 = n.

  Independientemente de la forma del árbol (es decir, si es equilibrado o si
  es degenerado, o ninguna de las dos cosas), esta recurrencia cumple que T(n)
  pertence a O(n). Por tanto, el coste de `analizar` es lineal con
  respecto al número de nodos del árbol de entrada.
 */

// Implementa aquí la función para tratar UN caso de prueba.
void tratar_caso() {
  BinTree<char> t = read_tree<char>(cin);
  auto [eq, raq, _] = analizar(t);
  if (raq) {
    cout << "RAQUITICO\n";
  } else if (eq) {
    cout << "EQUILIBRADO\n";
  } else {
    cout << "NADA\n";
  }
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
