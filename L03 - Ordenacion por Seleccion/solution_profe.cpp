/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */


/*
 * Solución práctica L03 - Ordenación por selección
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 


/*
  Implementación de listas doblemente enlazadas circulares

  https://github.com/manuelmontenegro/ED/blob/main/lineales/list_linked_double_v4/list_linked_double.h

*/

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

  // Implementa este método más abajo
  void sort_and_dedup();

private:
  Node *head;
  int num_elems;

  Node *nth_node(int n) const;
  void delete_nodes();
  void copy_nodes_from(const ListLinkedDouble &other);

  // Métodos privados. Impleméntalos más abajo
  Node *minimum(Node *begin, Node *end) const;
  void detach(Node *n);
  void attach(Node *n, Node *position);
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


/*
  Coste: O(N), donde N es el número de nodos que hay entre begin y end.

  Cuando comienza el bucle, cur empieza en el nodo de después de begin, y va
  avanzando hasta llegar a end. En cada iteración realiza operaciones de
  coste constante.

 */
ListLinkedDouble::Node * ListLinkedDouble::minimum(Node *begin, Node *end) const {
  Node *result = begin;
  Node *cur = begin->next;

  while (cur != end) {
    if (cur->value < result->value) {
      result = cur;
    }
    cur = cur->next;
  }
  return result;
}

/*
  Coste O(1)
 */
void ListLinkedDouble::detach(Node *n) {
  n->next->prev = n->prev;
  n->prev->next = n->next;
}

/*
  Coste O(1)
 */
void ListLinkedDouble::attach(Node *n, Node *position) {
  n->next = position->next;
  n->prev = position;
  position->next->prev = n;
  position->next = n;
}

/*
  Coste O(N^2), donde N es la longitud de la lista.

  Tiene un bucle con N iteraciones. En cada iteración se hace una llamada a
  minimum, que tiene coste O(N - k), donde k es el índice del nodo apuntado
  por cur. Como k avanza desde 0 hasta N, el coste del algoritmo es
  cuadrático con respecto a la longitud de la lista.
 */
void ListLinkedDouble::sort_and_dedup() {
  Node *prev = head;
  Node *cur = head->next;

  // Invariantes: el segmento desde head hasta prev está ordenado.
  //              prev es el nodo anterior a cur
  while (cur != head) {
    // Busco el mínimo entre la parte que está sin ordenar.
    Node *min = minimum(cur, head);
    // Desengancho el mínimo
    detach(min);
    // Si el valor mínimo coincide con el valor de prev (suponiendo que no
    // estamos en la primera iteración), es un duplicado => lo eliminamos.
    if (prev != head && prev->value == min->value) {
      delete min;
      cur = prev->next;
      num_elems--;
    } else {
      // De lo contrario, lo insertamos después de prev.
      attach(min, prev);
      prev = min;
      cur = min->next;
    }
  }
}

using namespace std;

void tratar_caso() {
  int x;

  ListLinkedDouble l;
  cin >> x;
  while (x != -1) {
    l.push_back(x);
    cin >> x;
  }

  l.sort_and_dedup();
  cout << l << endl;
}


int main() {
  // La entrada comienza con el número de casos de prueba.
  int num_casos;
  cin >> num_casos;

  // Llamamos tantas veces a `tratar_caso` como nos diga el número.
  for (int i = 0; i < num_casos; i++) {
    tratar_caso();
  }

  return 0;
}
