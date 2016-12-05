#ifndef CIUDAD_H
#define CIUDAD_H

#include "ICiudad.h"

class Ciudad : public ICiudad{
public:
	virtual ~Ciudad() {}

	//PRE: -
	//POS: Devuelve la el nombre de la Ciudad
	Cadena ObtenerNombre() const {
		return nombre;
	};

	//PRE: -
	//POS: Devuelve el número interno de esa ciudad en el mapa
	nat ObtenerNumero() const {
		return numero;
	};
private:
	Cadena nombre;
	nat numero;
};

#endif