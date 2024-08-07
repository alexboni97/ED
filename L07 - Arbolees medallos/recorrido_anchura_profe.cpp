/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */


// Solución que realiza una variante del recorrido en anchura.
// Autor: Manuel Montenegro Montes

// Añade los #include que necesites
#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>  // Para la clase pair
#include <tuple>    // Para la clase tuple
#include <queue>

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




// Calcula el número de mellas utilizando un recorrido en anchura.
template <typename T>
int num_mellas(const BinTree<T> &t) {
  // Cola para el recorrido en anchura  
  queue<BinTree<T>> q;

  // Metemos la raíz en la lista de nodos pendientes
  q.push(t);
  // En el primer nivel siempre hay un nodo.
  int numero_nodos_nivel = 1;

  // En esta variable guardamos el número de mellas encontradas
  int result = 0;

  // Salimos del bucle cuando:
  //  - Hemos recorrido todo el árbol (por tanto es completo)
  //  - Tras recorrer un nivel, nos hemos encontrado mellas. Eso significa
  //    que hemos terminado de recorrer el penúltimo nivel y no necesitamos seguir.
  while (!q.empty() && result == 0) {

    // La variable `mella_ant` toma el valor true si en el último hijo observado
    // estaba vacío o no. Eso nos sirve para saber, cada vez que encontramos un hijo
    // vacío, si ese vacío es continuación de una mella anterior, o estamos empezando
    // una nueva mella.
    bool mella_ant = false;

    // Número de mellas encontradas en el nivel actual
    int mellas_nivel_act = 0;

    // Número de nodos para el siguiente nivel
    int numero_nodos_siguiente_nivel = 0;

    // Recorremos todos los nodos del nivel actual.
    for (int i = 0; i < numero_nodos_nivel; i++) {
      BinTree<T> act = q.front();
      q.pop();

      // Si el hijo izquierdo es vacío y en la iteración anterior no
      // había hijo derecho vacío, estamos empezando una nueva mella.
      if (act.left().empty()) {
        if (!mella_ant) mellas_nivel_act++;
        mella_ant = true;
      } else {
        mella_ant = false;
        q.push(act.left());
        numero_nodos_siguiente_nivel++;
      }

      // Si el hijo derecho es vacío y el hijo izquierdo examinado anteriormente
      // no era vacío, estamos empezando una nueva mella.
      if (act.right().empty()) {
        if (!mella_ant) mellas_nivel_act++;
        mella_ant = true;
      } else {
        mella_ant = false;
        q.push(act.right());
        numero_nodos_siguiente_nivel++;
      }
    }

    // Si la cola aún tiene elementos, incrementamos el resultado con el
    // número de mellas encontradas en el nivel actual.
    if (!q.empty()) {
      result += mellas_nivel_act;
    }

    // Actualizamos el número de nodos del nivel actual con los del nivel
    // siguiente, ya que es el que vamos a explorar en la siguiente iteración.
    numero_nodos_nivel = numero_nodos_siguiente_nivel;
  }

  return result;
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
