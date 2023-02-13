#include <iostream>
#include <algorithm>
#include <fstream>
#include "Arbin.h"

bool esGenealogico(Arbin<int> const& arbol, int & generacion) {
    if (arbol.esVacio()) {
        generacion = 0;
        return true;
    } else {
        int gen_iz, gen_dr;
        bool h_iz = esGenealogico(arbol.hijoIz(), gen_iz);
        bool h_dr = esGenealogico(arbol.hijoDr(), gen_dr);
        //La altura es 1+ la del mayor de los hijos
        generacion = 1 + std::max(gen_iz, gen_dr);

        if (!arbol.hijoIz().esVacio()) {
            //El primer hijo debe tener 18 años más que el padre
            h_iz = h_iz && (arbol.raiz() >= arbol.hijoIz().raiz() + 18);
            if (!arbol.hijoDr().esVacio())
                //el segundo hijo debe tener 2 años más que el hermano
                h_dr = h_dr && (arbol.hijoIz().raiz() >= arbol.hijoDr().raiz() + 2);
        }
        //si no hay hijo izquierdo no puede haber hijo derecho
        else
            h_dr= h_dr && arbol.hijoDr().esVacio();
        return h_iz && h_dr;
    }
}

void resuelveCaso() {
    Arbin<int> arbol = Arbin<int>::leerArbol(-1);
    int altura;
    bool sol = esGenealogico(arbol, altura);
    if (sol)
        std::cout << "SI " << altura << '\n';
    else
        std::cout << "NO\n";
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("../p254.t1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}