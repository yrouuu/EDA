#include <iostream>
#include <iomanip>
#include <fstream>
#include "Queue.h"

using namespace std;

template <typename T>
void resuelveCaso(const T& cent) {
	// leer los datos de la entrada
	Queue<T> cola, colegas;
	T pringao;
	int n;
	cin >> n;
	while (n != -1) {	//Rellenar la cola
		cola.push_back(n);
		cin >> n;
	}
	cin >> pringao >> n;
	while (n != -1) {	//Rellenar colegas
		colegas.push_back(n);
		cin >> n;
	}
	cout << cola << endl;	// escribir sol
	cola.colar(pringao,colegas);
	cout << cola << endl;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("../datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso(int());

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	//system("PAUSE");
#endif

	return 0;
}