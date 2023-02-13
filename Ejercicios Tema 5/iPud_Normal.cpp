//DARÁ TIMELIMIT EN EL JUEZ

#include <fstream>
#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <stdexcept>
#include <iostream>

using namespace std;


using cancion = string;
using artista = string;

class iPud {
private:

    struct InfoCancion { //cada cancion tiene un autor y su duración
        artista autor=" ";
        int duracion=0;
    };

    unordered_map<cancion, InfoCancion> canciones; //la colección son canciones con su información
    list<cancion> playlist; //la playlist
    list<cancion> recientes; //las canciones recientes
    int duracion_total; //duración total

public:
    //O(1)
    iPud() : duracion_total(0) {}

    //O(1)
    void addSong(cancion S, artista A, int D) {
        auto esta = canciones.insert({S, {A, D}});
        if (!esta.second)
            throw domain_error("addSong");
    }

    //O(C) hay que buscar si la canción es nueva o no
    void addToPlaylist(cancion S) {
        auto it = canciones.find(S);
        if (it == canciones.end())
            throw domain_error("addToPlaylist");
        auto song = it->second;
        if (find(playlist.cbegin(), playlist.cend(),S) == playlist.cend() ){//si la canción es nueva
            playlist.push_back(S);
            duracion_total += song.duracion;
        }

    }

    //O(1)
    cancion current() const {
        if (playlist.empty())
            throw domain_error("current"); //Por la salida del juez
        return playlist.front();
    }

    //O(C) hay que buscar si la canción está en recientes o no
    void play() {
        if (!playlist.empty()) {
            cancion song = playlist.front();
            playlist.pop_front();
            auto & datos_song = canciones[song];
            duracion_total -= datos_song.duracion;
            //actualizamos recientes
            auto pos_reciente = find(recientes.cbegin(), recientes.cend(), song);
            if (pos_reciente != recientes.cend() ) //si estaba en recientes se quita
                recientes.erase(pos_reciente);
            recientes.push_front(song); //en cualquier caso se añade al principio
        }
    }

    //O(1)
    int totalTime() const {
        return duracion_total;
    }

    //O(N) según el número de canciones recientes que pidan
    list<cancion> recent(int N) const {
        list<cancion> sol;
        auto it = recientes.begin();
        while (it != recientes.end() && N > 0) {
            sol.push_back(*it);
            ++it;
            --N;
        }
        return sol;
    }

    //
    void deleteSong(cancion S) {
        auto it = canciones.find(S);
        if (it != canciones.end()) { //Si la canción no estaba, no se hace nada
            int duracion_S = it->second.duracion;

            auto pos_playlist = find(playlist.cbegin(), playlist.cend(), S);
            auto pos_reciente = find(recientes.cbegin(), recientes.cend(), S);
            if (pos_playlist != playlist.end()) {
                playlist.erase(pos_playlist);
                duracion_total -= duracion_S;
            }
            if (pos_reciente != recientes.end())
                recientes.erase(pos_reciente);

            canciones.erase(it);
        }
    }
};


bool resuelveCaso() {
    string operacion;
    cin >> operacion;
    if (!cin)
        return false;
    cancion tit; artista aut; int dur;
    iPud ipud;
    while (operacion != "FIN") {
        try {
            if (operacion == "addSong") {
                cin >> tit >> aut >> dur;
                ipud.addSong(tit, aut, dur);
            } else if (operacion == "addToPlaylist") {
                cin >> tit;
                ipud.addToPlaylist(tit);
            } else if (operacion == "current") {
                tit = ipud.current(); // aunque no se hace nada, puede producir error
            } else if (operacion == "play") {
                try {
                    string tocando = ipud.current(); // para saber si la lista es vacía
                    ipud.play();
                    cout << "Sonando " << tocando << '\n';
                } catch (domain_error & e) {
                    cout << "No hay canciones en la lista\n";
                }
            }
            else if (operacion == "totalTime") {
                cout << "Tiempo total " << ipud.totalTime() << '\n';
            } else if (operacion == "recent") {
                int N;
                cin >> N;
                auto lista = ipud.recent(N);
                if (lista.empty())
                    cout << "No hay canciones recientes\n";
                else {
                    cout << "Las " << lista.size() << " mas recientes\n";
                    for (auto const& s : lista)
                        cout << "    " << s << '\n';
                }
            } else if (operacion == "deleteSong") {
                cin >> tit;
                ipud.deleteSong(tit);
            }
        } catch (domain_error & e) {
            cout << "ERROR " << e.what() << '\n';
        }
        cin >> operacion;
    }
    cout << "---\n";
    return true;
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("../p100.t1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso()) {}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}