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
  Componente 1:
  Componente 2:
*/
//@ </answer>


#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

class ListLinkedDouble {
private:
  struct Node {
    int value;
    Node *next;
    Node *prev;
  };

public:
  ListLinkedDouble() : num_elems(0) {
    head = new Node;
    head->next = head;
    head->prev = head;
  }

  ListLinkedDouble(const ListLinkedDouble &other) : ListLinkedDouble() {
    copy_nodes_from(other);
    num_elems = other.num_elems;
  }

  ~ListLinkedDouble() { delete_nodes(); }

  void push_front(const int &elem) {
    Node *new_node = new Node{elem, head->next, head};
    head->next->prev = new_node;
    head->next = new_node;
    num_elems++;
  }

  void push_back(const int &elem) {
    Node *new_node = new Node{elem, head, head->prev};
    head->prev->next = new_node;
    head->prev = new_node;
    num_elems++;
  }

  void pop_front() {
    assert(num_elems > 0);
    Node *target = head->next;
    head->next = target->next;
    target->next->prev = head;
    delete target;
    num_elems--;
  }

  void pop_back() {
    assert(num_elems > 0);
    Node *target = head->prev;
    target->prev->next = head;
    head->prev = target->prev;
    delete target;
    num_elems--;
  }

  int size() const { return num_elems; }

  bool empty() const { return num_elems == 0; };

  const int &front() const {
    assert(num_elems > 0);
    return head->next->value;
  }

  int &front() {
    assert(num_elems > 0);
    return head->next->value;
  }

  const int &back() const {
    assert(num_elems > 0);
    return head->prev->value;
  }

  int &back() {
    assert(num_elems > 0);
    return head->prev->value;
  }

  const int &operator[](int index) const {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }

  int &operator[](int index) {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }

  ListLinkedDouble &operator=(const ListLinkedDouble &other) {
    if (this != &other) {
      delete_nodes();
      head = new Node;
      head->next = head->prev = head;
      copy_nodes_from(other);
      num_elems = other.num_elems;
    }
    return *this;
  }

  void display(std::ostream &out) const;

  void display() const { display(std::cout); }

  // El método se implementa más abajo, fuera de la definición de la clase.
  void zip(ListLinkedDouble &other);
  static void attach(Node *node, Node *before);  
  static void detach(Node *node);
private:
  // Declara aquí los métodos auxiliares privados que necesites,
  // pero impleméntalos más adelante entre las etiquetas <answer> y </answer>

  Node *head;
  int num_elems;

  Node *nth_node(int n) const;
  void delete_nodes();
  void copy_nodes_from(const ListLinkedDouble &other);
};

ListLinkedDouble::Node *ListLinkedDouble::nth_node(int n) const {
  int current_index = 0;
  Node *current = head->next;

  while (current_index < n && current != head) {
    current_index++;
    current = current->next;
  }

  return current;
}

void ListLinkedDouble::delete_nodes() {
  Node *current = head->next;
  while (current != head) {
    Node *target = current;
    current = current->next;
    delete target;
  }

  delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble &other) {
  Node *current_other = other.head->next;
  Node *last = head;

  while (current_other != other.head) {
    Node *new_node = new Node{current_other->value, head, last};
    last->next = new_node;
    last = new_node;
    current_other = current_other->next;
  }
  head->prev = last;
}

void ListLinkedDouble::display(std::ostream &out) const {
  out << "[";
  if (head->next != head) {
    out << head->next->value;
    Node *current = head->next->next;
    while (current != head) {
      out << ", " << current->value;
      current = current->next;
    }
  }
  out << "]";
}

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
  l.display(out);
  return out;
}

//@ <answer>
// ===========================================================
// Escribe tu solución por debajo de esta línea
// ===========================================================

// Si has definido operaciones auxiliares privadas en la clase, impleméntalas
// aquí.

// No olvides el coste!
void ListLinkedDouble::attach(Node *node, Node *before) {
  Node *prev=before->prev;
  prev->next=node;
  node->prev=prev;
  before->prev=node;
  node->next=before;
}

// No olvides el coste!
void ListLinkedDouble::detach(Node *node) {
    Node* aux=node->prev;
    aux->next=node->next;
    node->next->prev=aux;
    node->prev=nullptr;
    node->next=nullptr;
}

// Implementa el método pedido aquí. No te olvides del coste.
void ListLinkedDouble::zip(ListLinkedDouble &other) {
  Node * current=head->next;
  Node * next=current->next;
  Node * currOther=other.head->next;;
  Node * nextOther=currOther->next;
  if(other.empty())
  return;
  while (current!=head&&currOther!=other.head)
  {
    detach(currOther);
    attach(currOther,next);
    current=next;
    currOther=nextOther;
    next=next->next;
    nextOther=nextOther->next;
    num_elems++;
  }
  while (currOther!=other.head)
  {
    detach(currOther);
    attach(currOther,current);
    currOther=nextOther;
    nextOther=nextOther->next;
    num_elems++;
  }
  
}


void tratar_caso() {
  // Escribe aquí el código para leer de la entrada
  // un caso de prueba y procesarlo.
  int n,m,num;
  ListLinkedDouble lista,other;
  cin>>n;
  for (int i = 0; i < n; i++)
  {
    cin>>num;
    lista.push_back(num);
  }
  cin>>m;
    for (int i = 0; i < m; i++)
  {
    cin>>num;
    other.push_back(num);
  }
  lista.zip(other);
  lista.display();
  cout<<endl;

}

//@ </answer>
// ===========================================================
// No modifiques nada por debajo de esta línea
// ===========================================================

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  int num_casos;
  std::cin >> num_casos;

  while (num_casos > 0) {
    tratar_caso();
    num_casos--;
  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
