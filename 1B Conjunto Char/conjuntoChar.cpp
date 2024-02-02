#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
#include <assert.h>
using namespace std;
const int MAX_CHARS=26;

class ConjuntoChar {
    public:
        ConjuntoChar();
        bool pertenece(char letra) const;
        void anyadir(char letra);
        int busqueda_binaria(char letra)const;
    private:
        int num_elems;
        char elems[MAX_CHARS];
};
        
int ConjuntoChar:: busqueda_binaria(char letra)const{
    int pos=num_elems;
    int i=0;
    while(i<num_elems){
        if(this->elems[i]<letra)return i+1;
        i++;
    }
    return pos;
}

bool ConjuntoChar:: pertenece(char letra) const{
    int  i=busqueda_binaria(letra);
    if(i<num_elems&&this->elems[i]==letra){
        return true;
    }else 
    return false;
}

void ConjuntoChar  :: anyadir(char letra){
    int a=busqueda_binaria(letra);
    if(!pertenece(letra)){
        for(int j=num_elems;j<a;j++){
            this->elems[j]=this->elems[j-1];
        }
        this->elems[a]=letra;
        this->num_elems++;
    }
}


