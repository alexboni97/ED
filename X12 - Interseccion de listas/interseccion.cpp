




// Intersección de dos listas enlazadas simples
// --------------------------------------------
// Estructuras de datos

#include <iostream>
#include <cassert>
#include <fstream>
#include <ostream>

using namespace std;

/*
 * Implementación del TAD Lista mediante listas enlazadas simples.
 */

class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() {
        head = new Node;
        head->next = nullptr;
    }

    ~ListLinkedSingle() { delete_list(head); }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) {}

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head->next };
        head->next = new_node;
    }

    void push_back(const int& elem);

    void pop_front() {
        assert(head->next != nullptr);
        Node* old_head = head->next;
        head->next = head->next->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const { return head->next == nullptr; };

    const int& front() const {
        assert(head->next != nullptr);
        return head->next->value;
    }

    int& front() {
        assert(head->next != nullptr);
        return head->next->value;
    }

    const int& back() const { return last_node()->value; }

    int& back() { return last_node()->value; }

    const int& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    void display(std::ostream& out) const;

    void display() const { display(std::cout); }

    void intersect(const ListLinkedSingle& other);

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;
};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(const int& elem) {
    Node* new_node = new Node{ elem, nullptr };
    last_node()->next = new_node;
}

void ListLinkedSingle::pop_back() {
    assert(head->next != nullptr);
    Node* previous = head;
    Node* current = head->next;

    while (current->next != nullptr) {
        previous = current;
        current = current->next;
    }

    delete current;
    previous->next = nullptr;
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node* current = head->next;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}

ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
    out << "[";
    if (head->next != nullptr) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}


// Implementa aquí la función pedida
void ListLinkedSingle::intersect(const ListLinkedSingle& other) {
    
    if (this->empty() || other.empty()) {
        // Si alguna de las listas está vacía, la intersección es una lista vacía.
        delete_list(this->head->next);
        this->head->next = nullptr;
        return;
    }

    Node* curr = this->head->next;
    Node* prev = this->head;
    Node* aux_prev = other.head;
    Node* aux = other.head->next;

    while (curr != nullptr && aux != nullptr) {
        if (curr->value < aux->value) {
            // Eliminar el nodo actual de `this`
            Node* next = curr->next;
            prev->next = next;
            delete curr;
            curr = next;
        }
        else if (curr->value > aux->value) {
            // Eliminar el nodo actual de `other`
            Node* next = aux->next;
            aux_prev->next = next;
            delete aux;
            aux = next;
        }
        else {
            // Elementos iguales, avanzar en ambas listas
            prev = curr;
            curr = curr->next;
            aux_prev = aux;
            aux = aux->next;
        }
    }

    // Eliminar los nodos restantes en `this` si quedaron elementos no intersectados
    while (curr != nullptr) {
        Node* next = curr->next;
        prev->next = next;
        delete curr;
        curr = next;
    }

    // Eliminar los nodos restantes en `other` si quedaron elementos no intersectados
    while (aux != nullptr) {
        Node* next = aux->next;
        aux_prev->next = next;
        delete aux;
        aux = next;
    }

    
}


using namespace std;


// Función para tratar un caso de prueba
void tratar_caso() {

    ListLinkedSingle xs, zs;

    int tamanyo = 0;

    cin >> tamanyo;

    for (int i = 0; i < tamanyo; i++)
    {
        int numero;
        cin >> numero;
        xs.push_back(numero);
    }


    cin >> tamanyo;

    for (int i = 0; i < tamanyo; i++)
    {
        int num;
        cin >> num;
        zs.push_back(num);
    }

    xs.intersect(zs);

    xs.display(cout);

    cout << "\n";

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
