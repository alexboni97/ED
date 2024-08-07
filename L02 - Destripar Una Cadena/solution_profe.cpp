/*
 * ---------------------------------------------------
 *            Solución a la práctica L02
 * ---------------------------------------------------
 *             Manuel Montenegro Montes
 * ---------------------------------------------------
 */


#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 


/*
  Implementación de listas enlazadas simples vista en clase.

  https://github.com/manuelmontenegro/ED/tree/main/lineales/list_linked_single_v2

  En este caso, los valores contenidos en los nodos no son de tipo entero,
  sino de tipo char, porque es lo que requiere el ejercicio. En la Semana 4
  veremos cómo hacer que una misma implementación del TAD Lista pueda
  aplicarse a distintos tipos de elementos (int, char, string, etc.)
*/
class ListLinkedSingle {
private:
  struct Node {
    char value;
    Node *next;
  };

public:
  ListLinkedSingle(): head(nullptr) { }

  // Nuevo constructor. Se implementará fuera de la clase.
  // Mira más abajo para ver dónde tienes que implementarlo.
  ListLinkedSingle(const std::string &text);

  ~ListLinkedSingle() {
    delete_list(head);
  }

  ListLinkedSingle(const ListLinkedSingle &other)
    : head(copy_nodes(other.head)) { }

  void push_front(const char &elem) {
    Node *new_node = new Node { elem, head };
    head = new_node;
  }

  void push_back(const char &elem);

  void pop_front() {
    assert (head != nullptr);
    Node *old_head = head;
    head = head->next;
    delete old_head;
  }

  void pop_back();

  int size() const;

  bool empty() const {
    return head == nullptr;
  };
  
  const char & front() const {
    assert (head != nullptr);
    return head->value;
  }

  char & front() {
    assert (head != nullptr);
    return head->value;
  }

  const char & back() const {
    return last_node()->value;
  }

  char & back() {
    return last_node()->value;
  }
  
  const char & at(int index) const {
    Node *result_node = nth_node(index);
    assert (result_node != nullptr);
    return result_node->value;
  }

  char & at(int index) {
    Node *result_node = nth_node(index);
    assert (result_node != nullptr);
    return result_node->value;
  }

  void display(std::ostream &out) const;
  void display() const {
    display(std::cout);
  }

  // Método `destripar`. Se implementará fuera de la clase.
  // Mira más abajo para ver dónde tienes que implementarlo.
  void destripar(ListLinkedSingle &dest);

private:
  Node *head;

  void delete_list(Node *start_node);
  Node *last_node() const;
  Node *nth_node(int n) const;
  Node *copy_nodes(Node *start_node) const;

};

ListLinkedSingle::Node * ListLinkedSingle::copy_nodes(Node *start_node) const {
  if (start_node != nullptr) {
    Node *result = new Node { start_node->value, copy_nodes(start_node->next) };
    return result;
  } else {
    return nullptr;
  }
}

void ListLinkedSingle::delete_list(Node *start_node) {
  if (start_node != nullptr) {
    delete_list(start_node->next);
    delete start_node;
  }
}

void ListLinkedSingle::push_back(const char &elem) {
  Node *new_node = new Node { elem, nullptr };
  if (head == nullptr) {
    head = new_node;
  } else {
    last_node()->next = new_node;
  }
}

void ListLinkedSingle::pop_back() {
  assert (head != nullptr);
  if (head->next == nullptr) {
    delete head;
    head = nullptr;
  } else {
    Node *previous = head;
    Node *current = head->next;

    while (current->next != nullptr) {
      previous = current;
      current = current->next;
    }

    delete current;
    previous->next = nullptr;
  }
}

int ListLinkedSingle::size() const {
  int num_nodes = 0;

  Node *current = head;
  while (current != nullptr) {
    num_nodes++;
    current = current->next;
  }

  return num_nodes;
}


ListLinkedSingle::Node * ListLinkedSingle::last_node() const {
  assert (head != nullptr);
  Node *current = head;
  while (current->next != nullptr) {
    current = current->next;
  }
  return current;
}

ListLinkedSingle::Node * ListLinkedSingle::nth_node(int n) const {
  assert (0 <= n);
  int current_index = 0;
  Node *current = head;

  while (current_index < n && current != nullptr) {
    current_index++;
    current = current->next;
  }

  return current;
}

void ListLinkedSingle::display(std::ostream &out) const {
  out << "[";
  if (head != nullptr) {
    out << head->value;
    Node *current = head->next;
    while (current != nullptr) {
      out << ", " << current->value;
      current = current->next;
    }
  }
  out << "]";
}

// Implementa el constructor y el método pedidos. Indica y justifica el coste
// antes de cada implementación, mediante un comentario.


// Coste: lineal con respecto a la longitud de la cadena pasada como parámetro.
//
// Si N es la longitud de la cadena, el bucle hace N - 1 iteraciones, y dentro
// del bucle se hacen operaciones de coste O(1). Por tanto, el constructor
// tiene coste O(N)
ListLinkedSingle::ListLinkedSingle(const std::string &text): ListLinkedSingle() {
                                                            // ^ Llamamos al constructor por defecto
                                                            //   para que inicialice head a nullptr
  // Si la cadena es vacía, dejamos head a nullptr
  if (text.length() != 0) {
    // Creamos un nodo que almacene el primer carácter, y hacemos
    // que sea la nueva cabeza
    head = new Node { text[0], nullptr };
    // La variable `last` contendrá el último nodo creado
    Node *last = head;

    // Creamos los nodos de los demás caracteres, y los añadimos.
    for (int i = 1; i < text.length(); i++) {
      Node *nuevo = new Node { text[i], nullptr };
      last->next = nuevo;
      last = nuevo;
    }
  }
}


// Coste: lineal con respecto a la longitud de la lista this

// En el método hay dos bucles. El primero de ellos recorre la lista hasta la
// primera letra. El segundo continúa desde esa misma posición hasta el final
// de la lista. Por tanto, entre ambos bucles se hacen tantas iteraciones
// como elementos hay en `this`. Dentro de cada uno se realizan operaciones
// de coste O(1). Por tanto, el coste del método es O(N), donde N es la
// longitud de la lista.

void ListLinkedSingle::destripar(ListLinkedSingle &dest) {
  Node *prev = nullptr;
  Node *cur = head;

  // Buscamos el primer nodo que tenga una letra.
  while (cur != nullptr && cur->value >= '0' && cur->value <= '9') {
    prev = cur;
    cur = cur->next;
  }

  // En este punto `cur` apunta a la primera letra encontrada, y `prev` apunta
  // al anterior (o a nullptr) si la lista empieza por una letra.

  // Actualizamos las cabezas de ambas listas. `head` ahora apunta a la
  // primera letra encontrada y `dest.head` apunta al primer número.
  if (prev != nullptr) {
    dest.head = head;
    head = cur;    
  }

  // Buscamos la última letra de la cadena. Para ello recorremos toda la
  // lista. Cada vez que encontremos una letra, la guardamos en
  // `last_letter`
  Node *last_letter = nullptr;
  while (cur != nullptr) {
    if (cur->value < '0' || cur->value > '9') {
      last_letter = cur;
    }
    cur = cur->next;
  }

  // En este punto, `last_letter` apunta a la última letra de la cadena, o a
  // nullptr si no hay letras.

  // rest es el nodo que estará detrás de `last_letter` (si este último es
  // distinto de nullptr).
  Node *rest = nullptr;
  if (last_letter != nullptr) {
    rest = last_letter->next;
    last_letter->next = nullptr;
  }

  // Conectamos prev con rest. Si no había prev, entonces es la cabeza de dest
  // la que apuntará a rest.
  if (prev != nullptr) {
    prev->next = rest;
  } else {
    dest.head = rest;
  }
}

using namespace std;


void tratar_caso() {
  string str;
  cin >> str;

  ListLinkedSingle l1(str);
  ListLinkedSingle l2;

  l1.destripar(l2);

  // Aquí utilizamos display() porque en este momento no conocíamos la
  // sobrecarga de operadores, pero en las siguientes prácticas ya se podrá
  // utilizar: cout << l1 << '\n' << l2 << '\n';
  l1.display(); cout << '\n';
  l2.display(); cout << '\n';
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
