#ifndef HORA_H
#define HORA_H

class Hora {
	// Clase Hora

public:


	
	Hora(int hora, int minuto, int segundo) {
		
		this->hora = hora;
		this->minuto = minuto;
		this->segundo = segundo;
	}
	
	int get_hora() {
		return this->hora;
	}

	int get_minuto() {
		return this->minuto;
	}

	int get_segundo() {
		return this->segundo;
	}

	friend bool operator < (Hora const& h1, Hora const& h2) {

		if (h1.hora > h2.hora) return false;
		if (h1.hora < h2.hora) return true;
		if (h1.hora == h2.hora) {
			
			if (h1.minuto > h2.minuto) return false;
			if (h1.minuto < h2.minuto) return true;
			if (h1.minuto == h2.minuto) {
			
				if (h1.segundo > h2.segundo) return false;
				if (h1.segundo < h2.minuto) return true;
				
			}
		
		}
		
	}

	friend bool operator == (Hora const& h1, Hora const& h2) {

		return h1.hora == h2.hora&& h1.minuto == h2.minuto&& h1.segundo == h2.segundo;
	}

private:

	int hora;
	int minuto;
	int segundo;

};



#endif /* HORA_H*/
