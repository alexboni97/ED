/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 *      EXAMEN FINAL - CONVOCATORIA EXTRAORDINARIA
 * ---------------------------------------------------
 *  Solución al ejercicio 3
 *  Autor: Manuel Montenegro Montes
 * ---------------------------------------------------
 */


#include <iostream>
#include <fstream>
#include <stdexcept>
#include <queue>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>



using namespace std;

class Camping {
public:

    // O(log D + log P), donde D es el número de días que la `parcela` está
    // reservada y P es el número de parcelas reservadas el `dia` pasado como
    // parámetro.
    void nueva_reserva(const string &persona, int parcela, int dia) {
        // Comprobamos que la persona no sea titular, o esté en alguna lista de espera
        if (titulares.count(persona) || personas_en_lista_espera.count(persona)) {  // O(1)
            throw domain_error("Persona ya ha reservado");
        }

        // Obtenemos la lista de espera de esa (parcela, dia)
        queue<string> &q = parcela_dia[parcela][dia];       // O(1) + O(log D)

        // Si está vacía, entonces la persona es titular
        if (q.empty()) {                                    // O(1)
            titulares[persona] = { parcela, dia };          // O(1)
            q.push(persona);                                // O(1)  
        } else {
            // Si no, pasa a estar en lista de espera
            personas_en_lista_espera.insert(persona);       // O(1)
            q.push(persona);                                // O(1)
        }

        // Actualizamos también `dia_ocupadas`.
        dia_ocupadas[dia].insert(parcela);                  // O(log P)
    }

    // O(log D + log P), donde D es el número de días en los que la parcela
    // del titular está reservada y P es el número de parcelas reservadas el
    // mismo día que la reserva del titular.
    void cancelar_reserva(const string &persona) {
        // Miramos si es titular de alguna reserva
        auto [parcela, dia] = buscar_reserva(persona);      // O(1)

        // Borramos a la persona de los titulares
        titulares.erase(persona);                           // O(1)

        // Obtenemos la cola correspondiente a (parcela, dia), y sacamos al
        // titular.
        queue<string> &q = parcela_dia[parcela][dia];       // O(1) + O(log D)
        q.pop();                                            // O(1)

        if (q.empty()) {                                    // O(1)
            // Si la cola se ha quedado vacía, entonces la parcela vuelve
            // a estar disponible ese día.
            parcela_dia[parcela].erase(dia);                // O(log D)
            if (parcela_dia[parcela].empty()) {             // O(1)
                parcela_dia.erase(parcela);                 // O(1)
            }
            dia_ocupadas[dia].erase(parcela);               // O(log P)
            if (dia_ocupadas[dia].empty()) {                // O(1)
                dia_ocupadas.erase(dia);                    // O(1)
            }
        } else {
            // Si la cola no se ha quedado vacía, el siguiente de la cola
            // pasa a ser el nuevo titular.
            string siguiente = q.front();                   // O(1)
            titulares[siguiente] = { parcela, dia };        // O(1)
            personas_en_lista_espera.erase(siguiente);      // O(1)
        }
    }

    // O(log D), donde D es el número de días en los que la parcela pasada como parámetro
    // está reservada
    string quien_reserva(int parcela, int dia) const {
        if (!parcela_dia.count(parcela) || !parcela_dia.at(parcela).count(dia)) {   // O(1) + O(log D)
            throw domain_error("Parcela no reservada");
        } else {
            // El titular es el primero de la cola asociada al par (parcela, dia).
            return parcela_dia.at(parcela).at(dia).front();         // O(1) + O(log D) + O(1)
        }
    }

    // O(log D), donde D es el número de días en los que la parcela del
    // titular pasado como parámetro está reservada
    bool puede_extender_reserva(const string &persona, int n) const {
        // Comprobamos que la persona sea titular de alguna reserva.
        auto [parcela, dia] = buscar_reserva(persona);      // O(1)
        
        // Dentro de las reservas de esa parcela, obtenemos el iterador
        // al día del titular.
        auto it = parcela_dia.at(parcela).find(dia);        // O(1) + O(log D)
        
        // Si incrementamos el iterador, tendremos la reserva siguiente que
        // hay de esa misma parcela.
        it++;                                               // O(1)
        
        // Si it llega a .end(), no hay reserva posterior. Por tanto, no hay
        // problema en extender la reserva.
        if (it == parcela_dia.at(parcela).end()) return true;   // O(1)

        // Si no, obtengo el día de la reserva posterior.
        int dia_siguiente = it->first;

        // Compruebo que la extensión de n días no solapa con dia_siguiente.
        return dia + n < dia_siguiente;
    }

    // O(log P), donde P es el número de parcelas reservadas el mismo día que
    // la reserva del titular pasado como parámetro.
    int menor_distancia_vecinos(const string &persona) const {
        // Comprobamos que la persona sea titular de alguna reserva.
        auto [parcela, dia] = buscar_reserva(persona);      // O(1)

        // Buscamos el conjunto de parcelas ocupadas durante ese día.
        const set<int> &ocupadas = dia_ocupadas.at(dia);    // O(1)

        // Buscamos en ese conjunto la parcela ocupada por el titular pasado
        // como parámetro.
        auto it = ocupadas.find(parcela);                   // O(log P)

        // dist_izq: distancia a la parcela más cercana por el lado izqueirdo
        // dist_der: distancia a la parcela más cercana por el lado derecho
        int dist_izq = -1, dist_der = -1;
        
        // Nos vamos a la parcela reservada anterior (si existe)
        if (it != ocupadas.begin()) {                       // O(1)
          auto it_anterior = it;
          it_anterior--;
          dist_izq = parcela - *it_anterior - 1;
        }

        // Nos vamos a la parcela reservada siguiente (si existe)
        auto it_sig = it; it_sig++;
        if (it_sig != ocupadas.end()) {                     // O(1)
          dist_der = *it_sig - parcela - 1;
        }

        // Devolvemos la menor de las dos distancias.
        if (dist_izq == -1) {
          return dist_der;
        } else if (dist_der == -1) {
          return dist_izq;
        } else {
          return min(dist_izq, dist_der);
        }
    }

private:
    struct Reserva {
        int parcela;
        int dia;
    };

    // Para cada persona que es titular de reserva, qué parcela y día ha
    // reservado.
    unordered_map<string, Reserva> titulares;
    
    // Para cada parcela, diccionario que asocia cada día con la lista de
    // espera. Esta lista incluye al titular (en primera posición). El
    // diccionario interno es ordenado, para poder implementar la operación
    // `puede_extender_reserva` de manera eficiente.
    unordered_map<int, map<int, queue<string>>> parcela_dia;

    // Para cada día, conjunto de parcelas que están ocupadas ese día. Es un
    // `set` ordenado para poder implementar `menor_distancia_vecinos` de
    // manera eficiente.
    unordered_map<int, set<int>> dia_ocupadas;

    // Conjunto de personas que están en alguna lista de espera. Lo
    // necesitamos para saber si una persona puede reservar o no.
    unordered_set<string> personas_en_lista_espera;


    // Operación auxiliar. Busca la reserva de un titular. Lanza excepción
    // si la persona no es titular de ninguna reserva.
    // Coste: O(1)
    Reserva buscar_reserva(const string &titular) const {
        auto it = titulares.find(titular);      // O(1)
        if (it == titulares.end()) {
            throw domain_error("No es titular de ninguna reserva");
        } else {
            return it->second;
        }
    }

};



// Función para tratar un caso de prueba.

bool tratar_caso() {
  string operacion;
  cin >> operacion;

  if (cin.eof()) return false;

  Camping cp;
  
  while (operacion != "FIN") {
    try {
      if (operacion == "nueva_reserva") {
        string nombre;
        int parcela, dia;
        cin >> nombre >> parcela >> dia;
        cp.nueva_reserva(nombre, parcela, dia);
        cout << "OK\n";
      } else if (operacion == "cancelar_reserva") {
        string nombre;
        cin >> nombre;
        cp.cancelar_reserva(nombre);
        cout << "OK\n";
      } else if (operacion == "quien_reserva") {
        int parcela, dia;
        cin >> parcela >> dia;
        string nombre = cp.quien_reserva(parcela, dia);
        cout << "(" << parcela << ", " << dia << ") reservada por " << nombre << '\n';
      } else if (operacion == "puede_extender_reserva") {
        string nombre;
        int num_dias;
        cin >> nombre >> num_dias;
        bool puede = cp.puede_extender_reserva(nombre, num_dias);
        cout << nombre << (puede ? " " : " no ") << "puede extender la reserva " << num_dias << " dias\n";
      } else if (operacion == "menor_distancia_vecinos") {
        string nombre;
        cin >> nombre;
        int dist = cp.menor_distancia_vecinos(nombre);
        if (dist == -1) {
          cout << "INFINITO\n";
        } else {
          cout << dist << '\n';
        }
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
  // Si estás ejecutando el programa en tu ordenador, las siguientes líneas
  // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
  // útil para no tener que teclear los casos de prueba por teclado cada vez
  // que ejecutas el programa.
  //
  // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
  // comenta las líneas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
  std::ifstream in("sample3.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  // Llamamos tantas veces a `tratar_caso` hasta que devuelva `false`
  while (tratar_caso()) { }

  // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}

