// Usuario del Juez ......72


#include <iostream>
#include <iomanip>
#include <fstream>

#include "Hora.h"


// función que resuelve el problema
bool resolver(Hora & h1, Hora & h2, Hora& menor, Hora& mayor) {

    bool igual = false;

    if (h1 == h2) igual = true;
    else {
        
        if (h1 < h2) {
            
            menor = { h1.get_hora(), h1.get_minuto(), h1.get_segundo() };
            mayor = { h2.get_hora(), h2.get_minuto(), h2.get_segundo() };
        }
        else {
        
            mayor = { h1.get_hora(), h1.get_minuto(), h1.get_segundo() };
            menor = { h2.get_hora(), h2.get_minuto(), h2.get_segundo() };
        
        }
    }

    return igual;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int h, m, s; char c;

    std::cin >> h >> c >> m >> c >> s;
    Hora h1 = {h,m,s};

    std::cin >> h >> c >> m >> c >> s;
    Hora h2 = { h,m,s };

    Hora menor = { 0,0,0 };
    Hora mayor = { 0,0,0 };

    bool iguales = false;

    iguales = resolver(h1,h2,menor,mayor);
    // escribir sol

    if (iguales == true) std::cout << "IGUALES\n";
    else {
        
        std::cout << std::setw(2) << std::setfill('0') << menor.get_hora() << ':' << std::setw(2) << menor.get_minuto() << ':' << std::setw(2) << menor.get_segundo()<< std::setfill(' ') << " "
        << std::setw(2) << std::setfill('0') << mayor.get_hora() << ':' << std::setw(2) << mayor.get_minuto() << ':' << std::setw(2) << mayor.get_segundo() << std::setfill(' ') << "\n";
    }
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}