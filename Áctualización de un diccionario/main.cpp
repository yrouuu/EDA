#include <iostream>
#include <sstream> //para strinstream
#include <list>
#include "TreeMap.h"
#include <string>
#include <fstream>
#include "HashMap.h"
#include <functional>

using namespace std;

typedef TreeMap<string,int> Diccionario;

//Con HashMap hay que ordenar la salida.
//typedef HashMap<string,int> Diccionario;

//1. Para TreeMap o map: O(n*log n) siendo n el número de elementos
//2. Para HashMap o unsorted_map: O(n)
//Leemos todos y hacer insert es logarítmico asumiendo que el árbol está equilibrado
void leerDiccionario(Diccionario& diccionario){
    string linea;
    getline(cin, linea);
    stringstream lin(linea); //procesar la línea
    string clave;
    int valor;
    while (lin >> clave) {
        lin >> valor;
        diccionario.insert(clave,valor);
    }
}

//O(k) siendo k el tamaño de la lista
void printLista(list<string>& l,ostream& sout){
	list<string>::iterator it = l.begin();
	if (it != l.end()){
		sout << *it;
		++it;
	}
	while (it != l.end()){
		sout << " " << *it;
		++it;
	}
	sout << endl;
}

//1. Si usamos TreeMap o map: contains y at son métodos de coste logarítmico
// O(n*log m + m*log n) con n el tamaño del diccionario antiguo y m el del nuevo
//
//2. Si usamos HashMap o unordered_map: contains y at son constantes pero como tenemos que ordenar
// O(n + m + k log k) el máximo entre recorrer cada diccionario y ordenar la mayor de las listas
void calcularCambiosIneficiente(const Diccionario& antiguo, const Diccionario& nuevo,
                     list<string>& mas, list<string>& menos, list<string>& star){
   Diccionario::ConstIterator itNuevo = nuevo.cbegin();
   while(itNuevo != nuevo.cend()){
        if (antiguo.contains(itNuevo.key())) {
            if (antiguo.at(itNuevo.key()) != itNuevo.value()) {
                star.push_back(itNuevo.key());
            }
        } else {
            mas.push_back(itNuevo.key());
        }
        ++itNuevo;
    }
    Diccionario::ConstIterator itAnt = antiguo.cbegin();
    while(itAnt != antiguo.cend()){
        if (!nuevo.contains(itAnt.key())) {
            menos.push_back(itAnt.key());
        }
        ++itAnt;
    }
    //ordenar si usamos HashMap
    //Ordenar una lista tiene coste O(k*log k)
    //mas.sort();
    //menos.sort();
    //star.sort();
}

//O(n+m) con n el tamaño del diccionario antiguo y m el del nuevo
void calcularCambios(const Diccionario& antiguo, const Diccionario& nuevo,
		             list<string>& mas, list<string>& menos, list<string>& star){
	Diccionario::ConstIterator itAnt = antiguo.cbegin();
	Diccionario::ConstIterator itNuevo = nuevo.cbegin();
	while (itAnt != antiguo.cend() && itNuevo != nuevo.cend()){
		if (itAnt.key() < itNuevo.key()){
			menos.push_back(itAnt.key());
			++itAnt;
		} else if (itAnt.key() > itNuevo.key()){
			mas.push_back(itNuevo.key());
			++itNuevo;
		} else { // las claves son iguales
			if (itAnt.value() != itNuevo.value())
				star.push_back(itAnt.key());
			++itAnt; ++itNuevo;
		}
	}

	while (itAnt != antiguo.cend()){
		menos.push_back(itAnt.key());
		++itAnt;
	}
	while (itNuevo != nuevo.cend()){
		mas.push_back(itNuevo.key());
		++itNuevo;
	}
}

//El coste es el de printLista: O(k)
void printCambios(list<string>& mas, list<string>& menos, list<string>& star){
	if (mas.empty() && menos.empty() && star.empty())
		cout << "Sin cambios\n";
	else {
		if (!mas.empty()){
			cout << "+ ";
			printLista(mas,cout);
		}
		if (!menos.empty()){
			cout << "- ";
			printLista(menos,cout);
		}
		if (!star.empty()){
			cout << "* ";
			printLista(star,cout);
		}
	}
	cout << "---\n";
}


void resuelveCaso(){
	Diccionario antiguo, nuevo;
	list<string> mas,menos;
	list<string> claves;
	leerDiccionario(antiguo);
	leerDiccionario(nuevo);
	calcularCambios(antiguo,nuevo,mas,menos,claves);
	printCambios(mas,menos,claves);
}

int main(){
#ifndef DOMJUDGE
    ifstream in("../p262.t1-2.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	int numCasos;
  	cin >> numCasos;
    cin.ignore(1); //ignorar salto de línea
    for (int i = 0; i < numCasos; i++){
		resuelveCaso();
	}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

return 0;
}
