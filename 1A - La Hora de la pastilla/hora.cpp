#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
#include <assert.h>
using namespace std;

using Duracion =int;
class Hora{
    public:
        Hora(int horas, int minutos, int segundos ): num_segundos(horas * 3600 + minutos * 60 + segundos){
            assert(0 <= horas && horas < 24);
            assert(0 <= minutos && minutos  < 60);
            assert(0 <= segundos &&  segundos < 60);
        }
        Hora hora_pastilla(const Hora &primera, const Hora &ultima, int num_pastillas, int i);
        
        Duracion diferencia(const Hora&otra)const;
        Hora suma(Duracion d)const;

    private:
        int num_segundos;
};
Duracion Hora::diferencia(const Hora&otra)const{
    if(this->num_segundos<otra.num_segundos){
        return otra.num_segundos-this->num_segundos;
    }else return 24*3600-this->num_segundos+otra.num_segundos;
}
Hora Hora ::suma(Duracion d)const{
    Hora result(0,0,0);
    result.num_segundos = (this->num_segundos + d) % (24 * 36000);
    return result;
}

Hora Hora :: hora_pastilla(const Hora &primera, const Hora &ultima, int num_pastillas, int i){
    Duracion num_segundos_dif = primera.diferencia(ultima);
    Duracion segundos_entre_pastillas = num_segundos_dif / (num_pastillas - 1);
    Duracion segundos_desde_primera = segundos_entre_pastillas * (i - 1);
    return primera.suma(segundos_desde_primera);
}
void resuelve(){
    int h,m,s,n;
    cin >> h >> m >> s;
    Hora inicio(h,m,s);
    cin >> h >> m >> s;
    Hora final(h,m,s);
    cin>> n;
    Hora solucion=inicio.hora_pastilla(inicio,final,n,0);
}
int main(){
    int n;
    
    cin>>n;
    for(int i=0;i<n;i++){
        resuelve();
    }
    return 0;
}
