/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 *      EXAMEN FINAL - CONVOCATORIA EXTRAORDINARIA
 * ---------------------------------------------------
 *  Solución al ejercicio 2
 *  Autor: Manuel Montenegro Montes
 * ---------------------------------------------------
 */


#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>


/*
  Implementación de árboles binarios.
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

using namespace std;


// Función auxiliar que devuelve dos resultados:
//
// Primera componente: tamaño de la sección mayor en todo el árbol
// Segunda componente: tamaño de la sección de la cual forma parte la raíz del árbol
pair<int, int> seccion_mayor_aux(const BinTree<int> &tree) {
  if (tree.empty()) {
    // Si el árbol es vacío, no tiene secciones. El tamaño máximo de sección
    // es 0.
    return {0, 0};
  } else {
    // max_iz es el tamaño de la sección mayor que hay en el hijo izquierdo
    // max_dr es el tamaño de la sección mayor que hay en el hijo derecho
    auto [max_iz, raiz_iz] = seccion_mayor_aux(tree.left());

    // raiz_iz es el tamaño de la sección que comienza en tree.left().root()
    // raiz_dr es el tamaño de la sección que comienza en tree.right().root()
    auto [max_dr, raiz_dr] = seccion_mayor_aux(tree.right());

    // Ahora vamos a comprobar qué tamaño tiene la sección a la que pertenece
    // la raíz del árbol.

    // Inicialmente, el tamaño es 1, porque contiene la raíz
    int seccion_raiz = 1;

    // Pero si la raíz del hijo izquierdo coincide con la raíz del árbol,
    // le añadimos el tamaño de la sección que contiene tree.left().root()
    if (!tree.left().empty() && tree.left().root() == tree.root()) {
      seccion_raiz += raiz_iz;
    }
    // Hacemos lo mismo con el derecho.
    if (!tree.right().empty() && tree.right().root() == tree.root()) {
      seccion_raiz += raiz_dr;
    }

    // La sección mayor en todo el árbol es el máximo entre:
    //  - La sección mayor en el hijo izquierdo
    //  - La sección mayor en el hijo derecho
    //  - La sección que comienza en la raíz del árbol

    return {max(max(max_iz, max_dr), seccion_raiz), seccion_raiz};
  }
}
// El coste de la función seccion_mayor_aux viene dado por la siguiente recurrencia:
//
//  T(0) = k1
//  T(n) = T(n_i) + T(n_d) + k2  (si n > 0)
//
// donde n es el número de nodos del árbol, y n_i y n_d denotan el número de
// nodos del hijo izquierdo e hijo derecho, respectivamente.
//
// Independientemente de la elección de n_i y n_d en cada llamada (siempre que
// se cumpla n = 1 + n_i + n_d), el coste de esta recurrencia es lineal con
// respecto a n. Por tanto, el coste de sección_mayor_aux es O(n), donde n es
// el número de nodos del árbol.
//


// Realiza la llamada inicial a seccion_mayor_aux, y se queda con el resultado
// que nos interesa.
// El coste es O(n), donde n es el tamaño del árbol pasado como parámetro, ya que
// solo realiza una llamada a seccion_mayor_aux, que tiene ese mismo coste.
int seccion_mayor(const BinTree<int> &tree) {
  auto [max_seccion, _] = seccion_mayor_aux(tree);
  return max_seccion;
}

// Función para tratar un caso de prueba.
void tratar_caso() {
  // Leemos un árbol de la entrada
  BinTree<int> t = read_tree<int>(cin);
  // Imprimimos el resultado tras llamar a area_mayor_sin_barreras
  cout << seccion_mayor(t) << endl;
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
  std::ifstream in("sample2.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  int num_casos;
  cin >> num_casos;
  
  for (int i = 0; i < num_casos; i++) {
    tratar_caso();
  }

  // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
