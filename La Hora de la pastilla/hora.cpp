#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
using namespace std;
using Duracion =int;
class Hora{
    public:
    Hora(int horas, int minutos, int segundos){
        this->num_segundos=horas*360+minutos*60+segundos;
    }
    (Hora) hora_pastilla(const Hora&primera,const Hora&ultima,int num_pastillas,int i){

    }
    Duracion diferencia(const Hora&otra)const;

    private:
    int num_segundos;
};
Duracion Hora::diferencia(const Hora&otra)const{
    Duracion tiempo=abs(this->num_segundos-otra.num_segundos);
    return tiempo;
}

void resuelve(){
    
}
int main(){
    int n;
    
    cin>>n;
    for(int i=0;i<n;i++){
        resuelve();
    }
    return 0;
}
