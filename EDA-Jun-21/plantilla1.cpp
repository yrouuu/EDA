// Problema interseccion de dos listas ordenadas

// IMPORTANTE

// Nombre y apellidos del alumno
// Usuario del juez de clase
// Usuario que has utilizado en esta prueba

#include <iostream>               
#include <fstream>
using namespace std;

#include "List.h"


/////////////////////////////////////////////////////////
// de aquí hacia abajo NO se puede modificar nada

inline std::ostream& operator<<(std::ostream & o, List<int> const& a) {
    a.print(o);
    return o;
}

List<int> leerLista() {
    List<int> lista;
    int n;
    cin >> n;
    while (n != 0) {
        lista.push_back(n);
        cin >> n;
    }
    return lista;
}

bool resuelveCaso() {
    List<int> lista1 = leerLista();
    List<int> lista2 = leerLista();

    lista1.interseccion(lista2);

    cout << lista1 << endl;
    return true;
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    int casos;
    cin >> casos;
    while (casos--) {
        resuelveCaso();
    }
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
