#include <sstream> //para strinstream
#include <iostream>
#include <fstream>
#include <string>
...

//Hay que elegir un diccionario.
//¿Necesitamos que esté ordenado? ¿Que no lo esté?
typedef ... Diccionario;

//Método para leer un diccionario
void leerDiccionario(Diccionario& diccionario){
    string linea;
    getline(cin, linea);
    stringstream lin(linea); //procesar la línea
    string clave;
    while (lin >> clave) {
       lin >> valor;
       diccionario.insert(clave,valor);
    }
}

//Método que hace el problema. Recibe los diccionarios antiguo y nuevo.
//Debe devolver los cambios en alguna/s estructura/s adecuada/s
void calcularCambios(const Diccionario& DiccionarioAntiguo,const Diccionario& DiccionarioNuevo, ...){
	...
}

//Método para escribir por pantalla los cambios en los diccionarios.
void printCambios(...){
	...
}

//Esqueleto para resuelve caso: leemos los diccionarios, calculamos
//los cambios y los sacamos por pantalla.
void resuelveCaso(){
    ...
    leerDiccionario(DiccionarioAntiguo);
    leerDiccionario(DiccionarioNuevo);
    calcularCambios(DiccionarioAntiguo,DiccionarioNuevo,...);
    printCambios(...);
}

//Método main.
int main(){
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	int numCasos;
  	std::cin >> numCasos;
    stad::cin.ignore(1); //ignorar salto de línea
    for (int i = 0; i < numCasos; i++){
		resuelveCaso();
	}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

return 0;
}
