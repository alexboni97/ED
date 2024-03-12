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




//@ <answer>
// ----------------------------------------------
// Modificar a partir de aquí
// ----------------------------------------------

// Define las funciones auxiliares que sean necesarias. Para cada una de
// ellas, indica y justifica su coste.
// template <typename T>
// int height(const BinTree<T> &tree){
//   if (tree.empty())  {
//     return 0;
//   }else{
//     return 1 + max(height(tree.left()), height(tree.right()));
//   }
// }

// template <typename T>
// pair<bool, int> raquitico(const BinTree<T> &tree, const int & heightB){
//   if (tree.left().empty() && tree.right().empty())  // Comprobacion nodo raiz --> RAQ
//     return {true, 0};
//   else{
//     bool raq_left = raquitico(tree.left(), heightB);
//     bool raq_right = raquitico.(tree.right(), heightB);
//     int height_left = height(tree.left());
//     int height_right = height(tree.right());
//     return raq_left & raq_right & abs(height_left - height_right) = 1 & abs(height_left - height_right);
//   }
// }

// template <typename T>
// pair<bool, int> balanced_height(const BinTree<T> &tree){
//   if (tree.empty()){
//     return {true, 0};
//   }else{
//     auto [bal_left, height_left] = balanced_height(tree.left());
//     auto [bal_right, height_right] = balanced_height(tree.right());
//     bool balanced = bal_left && bal_right && abs(height_left - height_right) <= 1;
//     int height = 1 + max(height_left, height_right);
//     return {balanced, height};
//   }
// }
template <typename T>
tuple<bool, bool,int,int> raquitico_height_repeatheight(const BinTree<T> &tree){
  //if (tree.left().empty() && tree.right().empty()){
  if (tree.empty()){
    return {true, true, 0, 1};
  }else{
    int repeat_max_height=0;
    auto [bal_left, raq_left, height_left, repeat_max_height_left] = raquitico_height_repeatheight(tree.left());
    auto [bal_right, raq_right, height_right, repeat_max_height_right] = raquitico_height_repeatheight(tree.right());
    bool balanced = bal_left && bal_right && abs(height_left - height_right) <= 1;
    bool raquitico = raq_left && raq_right && abs(max(height_left, height_right) - min(height_left, height_right) - 1) <= 1;
    int height;
    if(height_left == height_right&&!tree.left().empty()&&!tree.right().empty())
      repeat_max_height = repeat_max_height_left+repeat_max_height_right;
    else{
      if(height_left>height_right)
        repeat_max_height=repeat_max_height_left;
      else
        repeat_max_height=repeat_max_height_right;
    }
    height = max(height_left, height_right);
    height += 1 ;
    return {balanced, raquitico, height,repeat_max_height};
  }
}
// Implementa aquí la función para tratar UN caso de prueba.
void tratar_caso(){
  BinTree<char> t = read_tree<char>(cin);
  pair<bool, int> pairR;
  pair<bool, int> pairB;
  auto[balanced,raquitico,height,repeat_height]=raquitico_height_repeatheight(t);
  if (!balanced)
    cout << "NADA\n";
  else{
    if (raquitico&&repeat_height<=1&&height>=1)
      cout << "RAQUITICO\n";
    else
      cout << "EQUILIBRADO\n";
  }
 // cout<<height<<" "<<repeat_height<<endl;
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

  // La entrada comienza con el número de casos de prueba.
  int num_casos;
  cin >> num_casos;

  // Llamamos a `tratar_caso` tantas veces como el número anterior.
  for (int i = 0; i < num_casos; i++) {
    //cout<<"---"<<i+2<<"----\n";
    tratar_caso();
  }

  // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
