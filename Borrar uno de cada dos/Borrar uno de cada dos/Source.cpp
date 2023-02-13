// ROUYI WANG
// C72

#include <iostream>
#include <iomanip>
#include <fstream>

#include "Horas.h"
#include "linked_list_ed.h"

template <typename T >
class linked_list_ed_plus : public linked_list_ed <T > {
    using Nodo = typename linked_list_ed <T >::Nodo;
public:

    void mostrar() const {

        Nodo* aux = this->prim;
        while (aux != nullptr) {

            std::cout << std::setw(2) << std::setfill('0') << aux->elem.get_hora() << ':' << std::setw(2) << aux->elem.get_min() << ':' << std::setw(2) << aux->elem.get_seg() << std::setfill(' ') << " ";
            aux = aux->sig;

        }

        std::cout << "\n";
    }

    void eliminarPares(const int& n) {
    
        int i = 0;

        if (this->prim->sig != nullptr) {
        
            Nodo* pos = this->prim;
            Nodo* aux = this->prim;
            //Nodo* pos2 = this ->prim->sig;

            while (aux->sig != nullptr && i < n) {
            
                if (i % 2 != 0) {
                
                    
                
                }
                else {
                
                   
                    aux = aux->sig;
                
                }

               
                i++;
            }

            if (i % 2 == 1) {
            
                delete pos2;
                ant->sig = nullptr;
            
            }

        }

    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int n, h, m, s, i = 0;
    char c;

    std::cin >> n;

    if (n == 0) return false;

    linked_list_ed_plus <Horas> lista;

    while (n != 0 && i < n) {
        
        std::cin >> h >> c >> m >> c >> s;
        Horas hora(h, m, s);
        
        lista.push_back(hora);

        i++;

    }

    lista.eliminarPares(n);
    lista.mostrar();
   
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    
    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}