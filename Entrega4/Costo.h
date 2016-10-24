#pragma once
#include "Tupla.h"
class Costo {
public:
	Costo() {
		costs = Tupla<int, int, int, int>(INT_MAX, INT_MAX, INT_MAX, INT_MAX);
	}
	Costo(Tupla<int, int, int, int> t) {
		costs = t;
	}

	bool operator <(const Costo & c) const {
		if (costs.Dato1 == c.costs.Dato1 && costs.Dato2 == c.costs.Dato2 && costs.Dato3 == c.costs.Dato3) {
			return costs.Dato4 == c.costs.Dato4;
		} else if (costs.Dato1 == c.costs.Dato1 && costs.Dato2 == c.costs.Dato2) {
			return costs.Dato3 < c.costs.Dato3;
		} else if (costs.Dato1 == c.costs.Dato1) {
			return costs.Dato2 < c.costs.Dato2;
		}
		return costs.Dato1 < c.costs.Dato1;
	};

	bool operator >(const Costo & c) const {
		return !(*this < c || *this == c);
	};

	bool operator ==(const Costo & c) const {
		return costs == c.costs;
	};

	bool operator !=(const Costo & c) const {
		return !(*this == c);
	};

	bool operator >=(const Costo & c) const {
		return (*this > c || *this == c);
	};

	bool operator <=(const Costo & c) const {
		return (*this < c || *this == c);
	};

	void operator +=(const Costo & c) {
		costs.AsignarDato1(costs.Dato1 + c.costs.Dato1);
		costs.AsignarDato2(costs.Dato2 + c.costs.Dato2);
		costs.AsignarDato3(costs.Dato3 + c.costs.Dato3);
		costs.AsignarDato4(costs.Dato4 + c.costs.Dato4);
	};

	Costo & operator =(const Costo & c) {
		costs = Tupla<int,int,int, int>(c.costs.Dato1, c.costs.Dato2, c.costs.Dato3, c.costs.Dato4);
		return *this;
	};
private:
	Tupla<int, int, int, int> costs;
};