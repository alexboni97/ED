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
  Introduce aquí los nombres de los componentes del grupo:
  
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

void partition(const int &pivot);

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
  void display_reverse(std::ostream &out) const;

  void display_reverse() const { display_reverse(std::cout); }
  
  
  // Nuevo método
  // Se implementa más abajo
  void add_to(int index, int val);
  

private:
  Node *head;
  int num_elems;

  Node *nth_node(int n) const;
  void delete_nodes();
  void copy_nodes_from(const ListLinkedDouble &other);
  
  // Nuevos métodos
  // Se implementan más abajo
  static void attach(Node *node, Node *before);  
  static void detach(Node *node);
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

void ListLinkedDouble::display_reverse(std::ostream &out) const {
  out << "[";
  if (head->prev != head) {
    out << head->prev->value;
    Node *current = head->prev->prev;
    while (current != head) {
      out << ", " << current->value;
      current = current->prev;
    }
  }
  out << "]";
}

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
  l.display(out);
  return out;
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------

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


// El coste en el caso peor es de O(n-1), es decir, O(n) que es lineal, siendo n los nodos que tiene la lista, que tiene que recorrer en el peor de los casos para encontrar el nodo donde vamos a hacer el atach
void ListLinkedDouble::add_to(int index, int val) {
  int i = 0;
  Node *current = head->next;
  while (i < index)
  {
    current = current->next;
    i++;
  }
  current->value += val;
  Node *next = current->next;
  Node *prev = current->prev;
  if (current->value != prev->value || current->value != next->value)
  {
    detach(current);
    if (current->value > next->value)
    {
      while (next != head && next->value < current->value)
      {
        next = next->next;
      }
      attach(current, next);
    }
    else
    {
      while (prev != head && prev->value > current->value)
      {
        prev = prev->prev;
      }
      attach(current, prev->next);
    }
  }
}

void ListLinkedDouble::partition(const int &pivot){
  Node *current =head->next;
  Node *menor=nullptr;
  while (current!=head)
  {
    while(pivot>=current->value&&current!=head){
      if (menor == nullptr)
        current = current->next;
      else
      {
        Node *aux = current->next;
        detach(current);
        attach(current, menor);
        current = aux;
      }
    }
    while(pivot < current->value&&current!=head)
    {
      if(menor==nullptr){
        menor=current;
      }
      current=current->next;
    }
    
    
  }
  
}

//}}}  


// Función para tratar un caso de prueba
void tratar_caso() {
  int n;
  ListLinkedDouble lista;
  cin>>n;
  while (n!=0)
  {
    lista.push_back(n);
    cin >> n;
  }
  int pivot;
  cin>>pivot;
  lista.partition(pivot);

  lista.display();

  cout<<endl;
  lista.display_reverse();
  cout<<endl;


}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;

    cin >> numCasos;

    for (int i = 0; i < numCasos; i++)
    {
        tratar_caso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
     system("PAUSE");
#endif

     return 0;
}
