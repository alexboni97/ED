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
    (bool)menorque( Duracion duracion_congreso){
        if(dias<duracion_congreso.dias){
            if(horas<duracion_congreso.horas)
                if(minutos<duracion_congreso.minutos)
                    if(segundos<duracion_congreso.segundos)return true;
        
        }else
        return false;
    }
    (void)suma(Duracion duracion_actividades){
        minutos+=duracion_actividades.segundos/60;
        segundos%=60;
        horas+=duracion_actividades.minutos/60;
        minutos%=60;
        dias+=duracion_actividades.horas/24;
        horas%=24;
    }
};

bool caben_todas(const vector<Duracion>&duracion_actividades,const Duracion&duracion_congreso){
    Duracion total={0,0,0,0};
    int i=0;
    while(i<duracion_actividades.size()&&total.menorque(duracion_congreso)){
        total.suma(duracion_actividades[i]);
        i++;
    }
    return total.menorque(duracion_congreso);
    
}