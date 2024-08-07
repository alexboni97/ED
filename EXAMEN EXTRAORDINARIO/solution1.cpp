/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 *      EXAMEN FINAL - CONVOCATORIA EXTRAORDINARIA
 * ---------------------------------------------------
 *  Solución al ejercicio 1
 *  Autor: Manuel Montenegro Montes
 * ---------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 

using namespace std;

/*
  Implementación de listas doblemente enlazadas circulares con nodo fantasma.
*/

template <typename Elem> class ListLinkedDouble {
private:
  struct Node {
    Elem value;
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

  void push_front(const Elem &elem) {
    Node *new_node = new Node{elem, head->next, head};
    head->next->prev = new_node;
    head->next = new_node;
    num_elems++;
  }

  void push_back(const Elem &elem) {
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

  const Elem &front() const {
    assert(num_elems > 0);
    return head->next->value;
  }

  Elem &front() {
    assert(num_elems > 0);
    return head->next->value;
  }

  const Elem &back() const {
    assert(num_elems > 0);
    return head->prev->value;
  }

  Elem &back() {
    assert(num_elems > 0);
    return head->prev->value;
  }

  const Elem &operator[](int index) const {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }

  Elem &operator[](int index) {
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

  // Esta es la operación que tienes que implementar.
  ListLinkedDouble quitar_duplicados();

private:
  // Cabeza de la lista
  Node *head;
  // Número de elementos de la lista
  int num_elems;

  Node *nth_node(int n) const;
  void delete_nodes();
  void copy_nodes_from(const ListLinkedDouble &other);

  // Operaciones auxiliares. Se implementan más abajo

  // Desengancha un nodo de la lista enlazada
  void detach(Node *n);
  // Engancha un nodo a una lista enlazada, justo antes de position
  void attach(Node *n, Node *position);

};

template <typename Elem>
typename ListLinkedDouble<Elem>::Node *
ListLinkedDouble<Elem>::nth_node(int n) const {
  int current_index = 0;
  Node *current = head->next;

  while (current_index < n && current != head) {
    current_index++;
    current = current->next;
  }

  return current;
}

template <typename Elem> void ListLinkedDouble<Elem>::delete_nodes() {
  Node *current = head->next;
  while (current != head) {
    Node *target = current;
    current = current->next;
    delete target;
  }

  delete head;
}

template <typename Elem>
void ListLinkedDouble<Elem>::copy_nodes_from(const ListLinkedDouble &other) {
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

template <typename Elem>
void ListLinkedDouble<Elem>::display(std::ostream &out) const {
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

template <typename Elem>
std::ostream &operator<<(std::ostream &out, const ListLinkedDouble<Elem> &l) {
  l.display(out);
  return out;
}



// Coste: O(1)
template <typename Elem>
void ListLinkedDouble<Elem>::detach(Node *n) {
  n->next->prev = n->prev;
  n->prev->next = n->next;
}

// Coste: O(1)
template <typename Elem>
void ListLinkedDouble<Elem>::attach(Node *n, Node *position) {
  n->next = position;
  n->prev = position->prev;
  position->prev->next = n;
  position->prev = n;
}

// Coste: O(N), donde N es la longitud de la lista `this`. El método tiene un
// bucle que se ejecuta tantas veces como elementos tiene `this`. Dentro del
// bucle solamente se realizan operaciones de coste O(1).
template<typename Elem>
ListLinkedDouble<Elem> ListLinkedDouble<Elem>::quitar_duplicados() {
  ListLinkedDouble<Elem> result;

  // Mantenemos un puntero a nodo que se comparará con el siguiente de la
  // lista.
  Node *cur = head->next;

  // Repetimos mientras `cur` tenga un nodo después.
  while (cur->next != head) {
    if (cur->value == cur->next->value) {
      // Si el contenido de cur y cur->next coinciden, desenganchamos
      // cur->next y lo enganchamos al final de la lista resultado.
      Node *target = cur->next;
      detach(target);
      attach(target, result.head);
      num_elems--;
      result.num_elems++;
    } else {
      // Si no, avanzamos cur.
      cur = cur->next;
    }
  }
  
  return result;
}


// Función para tratar UN caso de prueba. La función `main` llamará a esta
// función `tratar_caso` tantas veces como casos de prueba hay en la
// entrada.

bool tratar_caso() {
  // Leemos el número de elementos de la lista
  int num_elems;
  cin >> num_elems;

  if (num_elems == -1) return false;

  // Leemos los elementos de la lista
  ListLinkedDouble<char> lista;
  for (int i = 0; i < num_elems; i++) {
    string letra; cin >> letra;
    lista.push_back(letra[0]);
  }

  // Llamamos a la función pedida, e imprimimos las dos listas: `this` y la
  // lista devuelta por el método.
  ListLinkedDouble<char> resto = lista.quitar_duplicados();
  cout << lista << '\n';
  cout << resto << '\n';

  return true;
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
  std::ifstream in("sample1.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  // Llamamos tantas veces a `tratar_caso` hasta que devuelva `false`
  while (tratar_caso()) { }

  // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
