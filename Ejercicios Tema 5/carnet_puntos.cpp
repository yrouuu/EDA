#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
using namespace std;

using DNI = string;

class carnet_puntos {

    unordered_map<DNI, int> conductores;  // Conductores y sus puntos

    vector<int> num_puntos; // para cada cantidad de puntos, el número de conductores con esos puntos

public:
    //O(1)
    carnet_puntos() : num_puntos(16) {}

    //O(1)
    void nuevo(DNI conductor) {
        auto datos = conductores.insert({conductor, 15});
        if (datos.second)
            ++num_puntos[15];
        else
            throw domain_error("Conductor duplicado");
    }

    //O(1)
    void quitar(DNI conductor, int puntos) {
        auto it = conductores.find(conductor);
        if (it == conductores.end())
            throw domain_error("Conductor inexistente");
        auto & p = it->second;
        --num_puntos[p];
        p = max(0, p - puntos);
        ++num_puntos[p];
    }

    //O(1)
    int consultar(DNI conductor) const {
        auto it = conductores.find(conductor);
        if (it == conductores.end())
            throw domain_error("Conductor inexistente");
        return it->second;
    }

    //O(1)
    int cuantos_con_puntos(int puntos) const {
        if (puntos < 0 || puntos > 15)
            throw domain_error("Puntos no validos");
        return num_puntos.at(puntos);
    }

};


bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;
    
    carnet_puntos dgt;
    
    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                cin >> dni;
                dgt.nuevo(dni);
            } else if (orden == "quitar") {
                cin >> dni >> punt;
                dgt.quitar(dni, punt);
            } else if (orden == "consultar") {
                cin >> dni;
                punt = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << punt << '\n';
            } else if (orden == "cuantos_con_puntos") {
                cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            } else
                cout << "OPERACION DESCONOCIDA\n";
        } catch (domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
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
