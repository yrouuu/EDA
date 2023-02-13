# ifndef HORAS
# define HORAS
# include <iostream>
# include <array>
# include <stdexcept>

class Horas {
public:
	Horas(): hora(0), min(0), seg(0) {}
	Horas(int h, int m, int s) : hora(h), min(m), seg(s) {
		//if (h < 0 || h > MAX_HORAS) throw std::overflow_error("Hora invalida");
		//else if (m < 0 || m > MAX_MIN_SEG) throw std::overflow_error("Minuto invalido");
		//else if (s < 0 || s > MAX_MIN_SEG)throw std::overflow_error("Segundo invalido");
	}

	Horas& operator=(Horas const& other) {
		if (this != &other) {
			hora = other.hora; min = other.min; seg = other.seg;
		}
		return *this;
	}

	int get_hora()const { return hora; }
	int get_min()const { return min; }
	int get_seg()const { return seg; }

	bool operator<(Horas const& h)const {
		if (hora < h.hora) return true;
		else if (hora > h.hora) return false;
		else if (min < h.min)return true;
		else if (min > h.min)return false;
		else if (seg < h.seg)return true;
		else return false;
	}

	bool operator==(Horas const& h) const {
		return hora == h.hora && min == h.min && seg == h.seg;
	}

private:
	const int MAX_HORAS = 23;
	const int MAX_MIN_SEG = 59;
	int hora, min, seg;
};

inline std::ostream& operator << (std::ostream& out, Horas const& h) {
	out << h.get_hora() << ' ' << h.get_min() << ' ' << h.get_seg() << '\n';
	return out;
}

inline std::istream& operator >> (std::istream& in, Horas& h) {
	int hora, min, seg;
	in >> hora >> min >> seg;
	h = Horas(hora, min, seg);
	return in;
}


#endif