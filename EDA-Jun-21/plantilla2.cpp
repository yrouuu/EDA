// Problema El regreso de los enanos

// IMPORTANTE

// Nombre y apellidos del alumno
// Usuario del juez de clase
// Usuario que has utilizado en esta prueba

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Arbin.h"



// Explicación del algoritmo



// Coste de la función bien justificado.




// Aqui las funciones del alumno



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    Arbin<string> arbol = Arbin<string>::leerArbol(".");

    // LLamada a la función ue resuelve el problema


    // Escribir los resultados

}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    int numCasos;
    cin >> numCasos;
    cin.ignore();
    for (int i = 0; i < numCasos; ++i) {resuelveCaso();}
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

