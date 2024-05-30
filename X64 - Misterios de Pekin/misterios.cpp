// Misterios de Pekín
// ------------------
// Estructuras de datos

// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>



using namespace std;


class MisteriosDePekin {
public:
  MisteriosDePekin(const string &culpable) {
    
  }

  void anyadir_rasgo(const string &sospechoso, const string &rasgo) {

  }

  vector<string> sospechosos() const {
    return {};
  }

  void nuevo_jugador(const string &nombre) {

  }

  void jugador_descarta(const string &jugador, const string &rasgo) {

  }

  bool jugador_enganyado(const string &jugador) const {
    return false;
  }

  bool puede_detener_culpable(const string &jugador) const {
    return false;
  }


private:
  struct tSospechoso
  {
    string nombre;
    unordered_set<string>rasgos;
    bool culpable;
  };
  unordered_set<tSospechoso>sospechosos;
  unordered_set<string>jugadores;
};


bool tratar_caso() {
  string culpable;
  cin >> culpable;

  if (cin.eof()) return false;

  MisteriosDePekin mp(culpable);
  cout << "OK" << endl;

  string comando;
  cin >> comando;

  while (comando != "FIN") {
    try {
      if (comando == "anyadir_rasgo") {
        string sospechoso, rasgo;
        cin >> sospechoso >> rasgo;
        mp.anyadir_rasgo(sospechoso, rasgo);
        cout << "OK" << endl;
      } else if (comando == "sospechosos") {
        bool primero = true;
        for (const string &s : mp.sospechosos()) {
          cout << (primero ? "" : " ") << s;
          primero = false;
        }
        cout << endl;
      } else if (comando == "nuevo_jugador") {
        string nombre;
        cin >> nombre;
        mp.nuevo_jugador(nombre);
        cout << "OK" << endl;
      } else if (comando == "jugador_descarta") {
        string nombre; string rasgo;
        cin >> nombre >> rasgo;
        mp.jugador_descarta(nombre, rasgo);
        cout << "OK" << endl;
      } else if (comando == "jugador_enganyado") {
        string nombre;
        cin >> nombre;
        bool enganyado = mp.jugador_enganyado(nombre);
        cout << nombre << (enganyado ? "" : " no") << " ha sido enganyado" << endl;
      } else if (comando == "puede_detener_culpable") {
        string nombre;
        cin >> nombre;
        bool puede = mp.puede_detener_culpable(nombre);
        cout << nombre << (puede ? "" : " no") << " puede detener al culpable" << endl;
      }
    } catch (exception &e) {
      cout << "ERROR: " << e.what() << endl;
    }

    cin >> comando;
  }

  cout << "---" << endl;

  return true;
}

int main() {
  while (tratar_caso()) {  }

  return 0;
}
