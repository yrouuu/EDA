#include <iostream>
#include <stdexcept>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <utility>

using namespace std;

using Partido = string;
using Estado = string;

class ConteoVotos {

private:
    struct InfoEstado {
        unordered_map<Partido, int> votos; //votos por partido
        int num_compromisarios;

        InfoEstado(int comp): num_compromisarios(comp) {}
    };

    unordered_map<Estado, InfoEstado> estados;
public:
  //O(1)
  void nuevo_estado(const Estado &nombre, int num_compromisarios) {
      auto [it, nuevo] = estados.insert({nombre, InfoEstado(num_compromisarios)});
      if (!nuevo)
          throw domain_error("Estado ya existente");
  }

  //O(1)
  void sumar_votos(const Estado &estado, const Partido &partido, int num_votos) {
      auto it = estados.find(estado);
      if (it == estados.end()) {
          throw std::domain_error("Estado no encontrado");
      } else {
          InfoEstado &info_estado = it->second;
          info_estado.votos[partido] += num_votos;
      }
  }

  //O(P)
  Partido ganador_en(const Estado &estado) const {
      auto it = estados.find(estado);
      if (it == estados.cend()) {
          throw std::domain_error("Estado no encontrado");
      } else {
          const InfoEstado &info_estado = it->second;
          int max = -1;
          Partido ganador;
          for (auto &[partido, num] : info_estado.votos) {
              if (num > max) {
                  max = num;
                  ganador = partido;
              }
          }
          return ganador;
      }
  }

  //Este es el método que hay que mejorar
  //Recorremos todos los estados, calculamos ganador_en y lo metemos ordenado
  //O(E * P * log P)
  //Después nos recorremos el mapa: O(P)
  vector<pair<Partido,int>> resultados() const {
    map<Partido, int> result_map;
    vector<pair<Partido, int>> result;
    for (auto &[est, infoE] : estados) {
      result_map[ganador_en(est)] += infoE.num_compromisarios;
    }

    for (auto &[partido, votos]: result_map) {
      result.push_back({partido, votos});
    }
    return result;
  }
};


bool resuelveCaso() {
    string comando;
    cin >> comando;
    if (!cin) return false;

    ConteoVotos elecciones;

    while (comando != "FIN") {
        try {
            if (comando == "nuevo_estado") {
                Estado estado;
                int num_compromisarios;
                cin >> estado >> num_compromisarios;
                elecciones.nuevo_estado(estado, num_compromisarios);
            } else if (comando == "sumar_votos") {
                Estado estado;
                Partido partido;
                int num_votos;
                cin >> estado >> partido >> num_votos;
                elecciones.sumar_votos(estado, partido, num_votos);
            } else if (comando == "ganador_en") {
                Estado estado;
                cin >> estado;
                Partido ganador  = elecciones.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << ganador << "\n";
            } else if (comando == "resultados") {
                vector<pair<Partido,int>> res = elecciones.resultados();
                for (auto it = res.cbegin(); it != res.cend(); ++it) {
                    cout << it->first << " " << it->second << "\n";
                }
            }
        } catch (std::exception &e) {
            cout << e.what() << "\n";
        }
        cin >> comando;
    }

    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("../p322.t1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while(resuelveCaso()) { }

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
