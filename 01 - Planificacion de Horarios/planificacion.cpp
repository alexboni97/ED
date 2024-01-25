#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
using namespace std;

struct Duracion
{
    int dias;
    int horas;
    int minutos;
    int segundos;
};

bool caben_todas(const vector<Duracion>&duracion_actividades,const Duracion&duracion_congreso){
    Duracion total={0,0,0,0};
    for(int i=0;i<duracion_actividades.size();i++){
        total.dias+=duracion_actividades[i].dias;
        total.horas+=duracion_actividades[i].horas;
        total.minutos+=duracion_actividades[i].minutos;
        total.segundos+=duracion_actividades[i].segundos;
    }
    total.minutos+=total.segundos/60;
    total.segundos%=60;
    total.horas+=total.minutos/60;
    total.minutos%=60;
    total.dias+=total.horas/24;
    total.horas%=24;
    if(total.dias<duracion_congreso.dias){
    if(total.horas<duracion_congreso.horas)
    if(total.minutos<duracion_congreso.minutos)
    if(total.segundos<duracion_congreso.segundos)return true;

    }else
    return false;
}