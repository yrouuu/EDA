#ifndef fecha_h
#define fecha_h

#include <iostream>
#include <iomanip>

class fecha {
   int dia, hora, minuto;
public:
   fecha(int d = 0, int h = 0, int m = 0) : dia(d), hora(h), minuto(m) {}

   int getDia() const {
       return dia;
   }

   int getHora() const {
       return hora;
   }

   int getMinuto() const {
       return minuto;
   }

   bool operator<(fecha const& other) const {
      return dia < other.dia ||
      (dia == other.dia && hora < other.hora) ||
      (dia == other.dia && hora == other.hora && minuto < other.minuto);
   }
};


inline std::ostream & operator<<(std::ostream & salida, fecha const& f) {
   salida << std::setfill('0') << std::setw(2) << f.getHora() << ':';
   salida <<std::setfill('0') << std::setw(2) << f.getMinuto();
   return salida;
}

#endif
