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
  su número de nodos viene dado por la siguiente recurrencia

  N(0) = 0
  N(1) = 1
  N(h) = 1 + N(h-1) + N(h-2), h >= 2

  donde h es la altura del árbol.

  Esto se explica aquí:

  https://docs.google.com/document/d/1M3leKcFWKEhsdsGepX55zdsDf34XfnxaB4Rs7rpxIJQ/edit?usp=sharing
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
// Segunda componente: altura

template <typename T>
tuple<bool, int> equilibrado(const BinTree<T> &t) {
  if (t.empty()) {
    return { true, 0 };
  } else {
    auto [eq_iz, alt_iz] = equilibrado(t.left());
    auto [eq_dr, alt_dr] = equilibrado(t.right());
    int alt = 1 + max(alt_iz, alt_dr);
    bool eq = eq_iz && eq_dr && abs(alt_iz - alt_dr) <= 1;

    return {eq, alt};
  }
}

/*
 Coste de la función `equilibrado`.

 Si n es el número de nodos del árbol pasado como parámetro. El coste T(n) en
 tiempo de la función se expresa mediante la siguiente recurrencia.

  T(0) = k1
  T(n) = T(ni) + T(nd) + k2  (si n > 0)

  donde k1 y k2 son constantes, y ni y nd son el número de nodos del hijo
  izquierdo y derecho, respectivamente, sabiendo que ni + nd + 1 = n.

  Independientemente de la forma del árbol (es decir, si es equilibrado o si
  es degenerado, o ninguna de las dos cosas), esta recurrencia cumple que
  T(n) pertence a O(n). Por tanto, el coste de `equilibrado` es lineal con
  respecto al número de nodos del árbol de entrada.
 */

// Función que calcula el número de nodos de un árbol
template <typename T>
int numero_nodos(const BinTree<T> &t) {
  if (t.empty()) {
    return 0;
  } else {
    return 1 + numero_nodos(t.left()) + numero_nodos(t.right());
  }
}

/*
 Coste de la función `numero_nodos`.

 O(n), donde n es el número de nodos del árbol pasado como parámetro.
 La recurrencia es la misma que en la función `equilibrado`.
 */



/*
  Calcula el número mínimo de nodos que ha de tener un árbol equilibrado de
  altura h.

  N(0) = 0
  N(1) = 1
  N(h) = 1 + N(h-1) + N(h-2), h >= 2

  Coste: O(h), ya que tiene un bucle que realiza h iteraciones.
 */
int num_minimo_nodos(int h) {  
  // La variable n contiene el valor N(0)
  // La variable m contiene el valor N(1)
  int n = 0;
  int m = 1;


  // Invariante:
  //   La variable n contiene el valor N(i)
  //   La variable m contiene el valor N(i+1)
  for (int i = 0; i < h; i++) {
    int e = m;      // Guardamos N(i+1) en la variable `e`
    m = n + m + 1;  // Actualizamos m con el valor de N(i+2)
    n = e;          // Actualizamos n con el valor de N(i+1)
  }

  // Al salir del bucle, se cumple i == h. Por el invariante, la variable n
  // contiene el valor N(h).
  return n;
}

void tratar_caso() {
  BinTree<char> t = read_tree<char>(cin);
  auto [eq, h] = equilibrado(t);
  bool raq = eq && numero_nodos(t) == num_minimo_nodos(h);
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
