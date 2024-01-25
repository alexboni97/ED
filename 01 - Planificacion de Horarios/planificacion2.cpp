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
using Duracion=int;
bool caben_todas(const vector<Duracion>&duracion_actividades,const Duracion&duracion_congreso){
    Duracion total=0;
    for(int i=0;i<duracion_actividades.size();i++){
        total+=duracion_actividades[i];
    }
    if(total<duracion_congreso)return true;
    else
    return false;
}