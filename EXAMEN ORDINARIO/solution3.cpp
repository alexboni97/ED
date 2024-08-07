/* ----------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ----------------------------------------------------
 *   Examen final. Convocatoria ordinaria (mayo 2024)
 *                   Ejercicio 3
 * ----------------------------------------------------
 */

/*
 * Solución por Manuel Montenegro Montes
 */

#include <iostream>
#include <fstream>
#include <list>
#include <stdexcept>
#include <set>
#include <map>
#include <unordered_map>


using namespace std;

class CasaDeSubastas {
public:

  // O(1)
  CasaDeSubastas() { }

  // O(1)
  void nuevo_participante(const string &part, int saldo_inicial) {
    // Comprobamos si el participante existe
    if (participantes.count(part)) {                      // O(1)
      throw domain_error("Participante ya existente");
    }
    // Comprobamos si el saldo inicial es correcto
    if (saldo_inicial <= 0) {
      throw domain_error("Saldo inicial no valido");
    }

    // Insertamos al nuevo participante con su saldo inicial
    InfoParticipante ip;
    ip.saldo = saldo_inicial;
    participantes.insert({part, ip});                     // O(1)
  }

  // O(1)
  void nueva_subasta(const string &obj, int puja_min) {
    // Comprobamos si el objeto existe
    if (objetos.count(obj)) {                             // O(1)
      throw domain_error("Objeto no valido");
    }
    // Comprobamos si la puja de salida es positiva
    if (puja_min <= 0) {
      throw domain_error("Puja inicial no valida");
    }
    // Insertamos el nuevo objeto con su valor de salida y con su
    // atributo `adjudicado` a false, ya que aún no se ha vendido
    InfoObjeto io;
    io.puja_minima = puja_min;
    io.adjudicado = false;
    objetos.insert({obj, io});                            // O(1)
  }

  // O(log P), donde P es el número de personas que han pujado por ese
  // objeto
  void nueva_puja(const string &part, const string &obj, int cantidad) {
    // Buscamos el participante y el objeto
    InfoParticipante &ip = buscar_participante(part);     // O(1)
    InfoObjeto &io = buscar_objeto(obj);                  // O(1)

    // Si el objeto ha sido vendido, lanzamos excepción
    if (io.adjudicado) {
      throw domain_error("Objeto no valido");
    }

    // Si el participante ya ha pujado por ese objeto, lanzamos
    // excepción
    if (ip.pujas.count(obj)) {                            // O(1)
      throw domain_error("Participante repetido");
    }

    // Si la cantidad excede el saldo del participante, o no llega
    // al valor mínimo, se lanza excepción.
    if (cantidad > ip.saldo || cantidad < io.puja_minima) {
      throw domain_error("Cantidad no valida");
    }

    // Obtenemos la lista de personas que han pujado esa cantidad. Si ninguna
    // persona ha pujado, se crea una lista vacía asociada a esa cantidad.
    list<string> &lista_pujas = io.pujas[cantidad];       // O(log P)

    // Insertamos a la persona al final de esa lista, y obtenemos un iterador
    // a esa posición.
    auto it_lista = lista_pujas.insert(lista_pujas.end(), part);  // O(1)

    // Actualizamos la información de esa persona, decrementando su saldo, y
    // añadiendo la puja a su tabla de pujas.
    ip.saldo -= cantidad;                                 // O(1)
    ip.pujas[obj] = {cantidad, it_lista};                 // O(1)
  }

  // O(S), donde S es el número de subastas ganadas por el participante
  // pasado como parámetro.
  list<string> subastas_ganadas(const string &part) const {
    // Buscamos la información del partipante
    const InfoParticipante &ip = buscar_participante(part);       // O(1)
    // Creamos una lista con los contenidos del conjunto ip.ganadas
    list<string> result(ip.ganadas.begin(), ip.ganadas.end());    // O(S)
    // Alternativamente, podría haberse creado una lista vacía, y recorrer
    // ip.ganadas, insertando los elementos recorridos en esa lista.

    // Devolvemos esa lista
    return result;
  }

  // O(Q * log P), donde Q es el número de pujas que ha hecho el participante, y
  // P es la cantidad máxima de pujas que ha recibido uno de los objetos por los que
  // ha pujado el participante.
  void abandonar_casa(const string &part) {
    InfoParticipante &ip = buscar_participante(part);       // O(1)
    for (auto &[obj, puja] : ip.pujas) {      // Se realizan tantas iteraciones como pujas ha hecho el participante
      auto [cantidad, it] = puja;
      objetos[obj].pujas[cantidad].erase(it);               // O(log P), donde P es el número de pujas que ha recibido el objeto
      if (objetos[obj].pujas[cantidad].empty()) {           // O(log P)
        objetos[obj].pujas.erase(cantidad);                 // O(log P)
      }
    }
    participantes.erase(part);                              // O(1)
  }

  
  // O(N + log S), donde N es el número de personas que han pujado por ese objeto
  // y S es el número de objetos ganados por el ganador de ese objeto.
  string cerrar_subasta(const string &obj) {
    InfoObjeto &io = buscar_objeto(obj);                    // O(1)
    if (io.adjudicado) {
      throw domain_error("Objeto no valido");
    }
    bool primero = true;
    string destinatario;

    // El bucle interno hace tantas iteraciones como participantes han pujado
    // por ese objeto, pero lo que hay dentro de if (primero) { ... } solo se
    // ejecuta una vez!!
    for (auto &[cantidad, pujadores] : io.pujas) {
      for (const string &pujador : pujadores) {
        if (primero) {
          participantes[pujador].ganadas.insert(obj);     // O(log S)
          destinatario = pujador;
          io.adjudicado = true;
          primero = false;
        } else {
          participantes[pujador].saldo += cantidad;       // O(1)
        }
        // Lo siguiente es opcional. Puede borrarse la puja del diccionario de
        // pujas del participante.
        
        // participantes[pujador].pujas.erase(obj);       // O(1)
      }
    }

    if (primero) {
      throw domain_error("Objeto no vendido");
    }

    return destinatario;
  }

private:
  // Información relativa a cada persona que participa en las subastas
  struct InfoParticipante {
    // Saldo de la persona
    int saldo;
    // Subastas que ha ganado
    set<string> ganadas;
    // Pujas que ha realizado por los objetos. Para cada objeto obj,
    // pujas[obj] contiene un par {x, it}, donde x es la cantidad pujada
    // e it es un iterador al elemento de la lista objetos[obj].pujas[x]
    unordered_map<string, pair<int, list<string>::iterator>> pujas;

  };

  // Información relativa a los objetos que son subastados
  struct InfoObjeto {
    // Valor mínimo que se puede pujar por él
    int puja_minima;
    // Si el objeto ya ha sido adjudicado a alguien
    bool adjudicado;
    // Pujas que ha recibido el objeto, ordenadas de mayor a menor según
    // cantidad. Para cada cantidad x, pujas[x] contiene la lista de
    // participantes que han pujado esa cantidad por ese objeto.
    map<int, list<string>, greater<int>> pujas;
  };

  // Diccionario de participantes
  unordered_map<string, InfoParticipante> participantes;
  // Diccionario de objetos subastados
  unordered_map<string, InfoObjeto> objetos;

  // Devuelve la información de un determinado participante, o lanza
  // excepción en caso de no existir
  // Coste: O(1)
  InfoParticipante & buscar_participante(const string &nombre) {
    auto it = participantes.find(nombre);     // O(1)
    if (it == participantes.end()) {
      throw domain_error("Participante no existente");
    } else {
      return it->second;
    }
  }

  // Devuelve la información de un determinado participante, o lanza
  // excepción en caso de no existir
  // Coste: O(1)
  const InfoParticipante & buscar_participante(const string &nombre) const {
    auto it = participantes.find(nombre);     // O(1)
    if (it == participantes.end()) {
      throw domain_error("Participante no existente");
    } else {
      return it->second;
    }
  }

  // Devuelve la información de un determinado objeto, o lanza
  // excepción en caso de no existir

  // Coste: O(1)
  InfoObjeto & buscar_objeto(const string &nombre) {
    auto it = objetos.find(nombre);         // O(1)
    if (it == objetos.end()) {
      throw domain_error("Objeto no valido");
    } else {
      return it->second;
    }
  }

};

//@ </answer>
// ------------------------------------------------------------------
// No modificar a partir de aquí
// ------------------------------------------------------------------


// Función para tratar un caso de prueba

bool tratar_caso() {
  string operacion;
  cin >> operacion;

  if (cin.eof()) return false;

  CasaDeSubastas cs;

  while (operacion != "FIN") {
    try {
      if (operacion == "nuevo_participante") {
        string part; int saldo;
        cin >> part >> saldo;
        cs.nuevo_participante(part, saldo);
        cout << "OK\n";
      } else if (operacion == "nueva_subasta") {
        string obj; int puja_min;
        cin >> obj >> puja_min;
        cs.nueva_subasta(obj, puja_min);
        cout << "OK\n";
      } else if (operacion == "nueva_puja") {
        string part, obj; int cantidad;
        cin >> part >> obj >> cantidad;
        cs.nueva_puja(part, obj, cantidad);
        cout << "OK\n";
      } else if (operacion == "subastas_ganadas") {
        string part;
        cin >> part;
        list<string> result = cs.subastas_ganadas(part);
        cout << part << " ha ganado:";
        for (const string &part : result) {
          cout << " " << part;
        }
        cout << "\n";
      } else if (operacion == "abandonar_casa") {
        string part;
        cin >> part;
        cs.abandonar_casa(part);
        cout << "OK\n";
      } else if (operacion == "cerrar_subasta") {
        string obj;
        cin >> obj;
        string ganador = cs.cerrar_subasta(obj);
        cout << obj << " ha sido ganado por: " << ganador << "\n";        
      }
    } catch (exception &e) {
      cout << "ERROR: " << e.what() << "\n";
    }
    cin >> operacion;
  }

  cout << "---\n";

  return true;
}

int main() {
  // Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
  while (tratar_caso()) { }
  return 0;
}
