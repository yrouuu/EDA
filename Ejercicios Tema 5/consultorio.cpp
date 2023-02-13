#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <utility>
#include <vector>
#include "fecha.h"

using namespace std;

using paciente = string;
using medico = string;

class consultorio {
    using citas = map<fecha, paciente>; //citas médicas

    unordered_map<medico, citas> horario; //horario completo del consultorio

public:
    //O(1)
    void nuevoMedico(medico const& m) {
        horario.insert({m, citas()});
    }

    //O(log P) con P = número de citas
    void pideConsulta(paciente const& p, medico const& m, fecha const& f) {
        auto it = horario.find(m);
        if (it == horario.end())
            throw invalid_argument("Medico no existente");
        else {
            if (it->second.find(f) != it->second.end()) //si está la fecha ya O(log P)
                throw invalid_argument("Fecha ocupada");
            else
                it->second[f] = p;
        }
    }

    //O(1)
    paciente siguientePaciente(medico const& m) const {
        auto it = horario.find(m);
        if (it == horario.end())
            throw invalid_argument("Medico no existente");
        else {
            auto & datos_medico = it->second;
            if (datos_medico.empty())
                throw invalid_argument("No hay pacientes");
            else
                return datos_medico.begin()->second;
        }
    }

    //O(1) amortizado
    void atiendeConsulta(medico const& m) {
        auto it = horario.find(m);
        if(it == horario.end())
            throw invalid_argument("Medico no existente");
        else {
            auto & datos_medico = it->second;
            if (datos_medico.empty())
                throw invalid_argument("No hay pacientes");
            else
                datos_medico.erase(datos_medico.begin()); //O(1) amortizado
        }
    }

    //O(P) donde P es el número de citas
    vector<pair<fecha,paciente>> listaPacientes(medico const& m, fecha const& f) {
        auto it = horario.find(m);
        if(it == horario.end())
            throw invalid_argument("Medico no existente");
        else {
            auto & datos_medico = it->second;
            vector<pair<fecha,paciente>> sol;
            for (auto & p : datos_medico) {
                if (f.getDia() == p.first.getDia())
                    sol.emplace_back(p);
            }
            return sol;
        }
    }

};


bool resuelveCaso() {
    int casos = 0;
   int N;
   cin >> N;
   if (!cin) return false;
   
   string inst; medico med; paciente pac; int d, h, m; char c;
   consultorio con;
   
   for (int i = 0; i < N; ++i) {
      try {
         cin >> inst;
         if (inst == "nuevoMedico") {
            cin >> med;
            con.nuevoMedico(med);
         } else if (inst == "pideConsulta") {
            cin >> pac >> med >> d >> h >> c >> m;
            con.pideConsulta(pac, med, fecha(d,h,m));
         } else if (inst == "siguientePaciente") {
            cin >> med;
            pac = con.siguientePaciente(med);
            cout << "Siguiente paciente doctor " << med << '\n';
            cout << pac << '\n';
         } else if (inst == "atiendeConsulta") {
            cin >> med;
            con.atiendeConsulta(med);
         } else if (inst == "listaPacientes") {
            cin >> med >> d;
            auto vec = con.listaPacientes(med, fecha(d,0,0));
            cout << "Doctor " << med << " dia " << d << '\n';
            for (auto p : vec) {
               cout << p.second << ' ' << p.first << '\n';
            }
         }
      } catch (invalid_argument e) { cout << e.what() << '\n'; }
   }
   cout << "---\n";
   
   return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
