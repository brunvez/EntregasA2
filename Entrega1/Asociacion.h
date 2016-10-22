#ifndef ASOCIACION_H
#define ASOCIACION_H

#include <iostream>
using namespace std;

template <class Dominio, class Rango>
class Asociacion;

template <class Dominio, class Rango>
ostream &operator<<(ostream& out, const Asociacion<Dominio, Rango> &o);

template <class Dominio, class Rango>
class Asociacion {
	// Flujo de salida
	friend ostream &operator<< <>(ostream &out, const Asociacion<Dominio, Rango> &o);

public:
	Asociacion();
	Asociacion(const Dominio &d);
	Asociacion(const Dominio &d, const Rango &r);
	Asociacion(const Asociacion &o);

	virtual ~Asociacion();

	Asociacion<Dominio, Rango> &operator=(const Asociacion<Dominio, Rango> &o);

	const Dominio &GetDominio() const;
	//void SetDominio(const Dominio &d);

	const Rango &GetRango() const;
	Rango &GetRangoInseguro() const;
	void SetRango(const Rango &r);

	bool operator==(const Asociacion<Dominio, Rango> &o) const;
	bool operator!=(const Asociacion<Dominio, Rango> &o) const;
	bool operator<(const Asociacion<Dominio, Rango> &o) const;
	bool operator>(const Asociacion<Dominio, Rango> &o) const;
	bool operator<=(const Asociacion<Dominio, Rango> &o) const;
	bool operator>=(const Asociacion<Dominio, Rango> &o) const;

private:
	Dominio d;
	Rango r;
};

#include "Asociacion.cpp"

#endif