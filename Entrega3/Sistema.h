#ifndef SISTEMA_H
#define SISTEMA_H

#include "Iterador.h"
#include "Tablero.h"
#include "ColaDePrioridadHeap.h"

class Sistema {
public:
	Sistema();

	~Sistema() { };

	void EstablecerTableroInicial(Tablero inicial);

	//Decide si el tablero inicial tiene solución. 
	bool TieneSolucion();

	//Retorna la cantidad mínima de movimientos necesarios para resolver el rompecabezas. Si no hay solución posible retorna −1. 
	int Movimientos();

	//Retorna un iterador de tableros con los movimientos necesarios para resolver el rompecabezas con movimientos mínimos.
	//Si no hay solución devuelve un iterador vacío. 
	Iterador<Tablero> Solucionar();

private:
	struct Estado {
		Tablero actual;
		int moves;
		Puntero<Estado> ant;
		Estado(Tablero &ini, int m, Puntero<Estado> e = nullptr) { actual = ini; moves = m; ant = e; }
		~Estado() { ant = nullptr;  };
	};
	bool tieneSol;
	Puntero<Estado> solucion;
};

#endif
