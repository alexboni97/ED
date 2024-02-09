
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>
class ListLinkedSingle {
public:
ListLinkedSingle();
~ListLinkedSingle();
ListLinkedSingle(const ListLinkedSingle &other);
void mezcla(ListLinkedSingle &li);

void push_front(const int &elem);
void push_back(const int &elem);
void pop_front();
void pop_back();
int size() const;
bool empty() const;
const int & front() const;
int & front();
const int & back() const;
int & back();
const int & at(int index) const;
int & at(int index);
void display() const;
private:
struct Node {
    int value;
    Node *next;
  };
Node *head;
};

void ListLinkedSingle ::mezcla(ListLinkedSingle &li){
    Node *prev=nullptr;
    Node *current=nullptr;
    Node *other=nullptr;
    if(li.head->value<=this->head->value){
        prev=li.head;
        current=this->head;
    }
    else prev=this->head;
    while(current->next==nullptr&&other->next==nullptr){
        if(current->value<=other->value){
            prev->next=current;
            prev=current;
            current=current->next;
        }else{
            prev->next=other;
            prev=other;
            other=other->next;
        }
    }
    
}


int main(){
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif



#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
    return 0;
}