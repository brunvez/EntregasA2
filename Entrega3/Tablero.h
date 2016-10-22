#ifndef TABLERO_H
#define TABLERO_H

#include "Matriz.h"
#include "Cadena.h"
#include "Iterador.h"

typedef unsigned int nat;

class Tablero{
public : 
	Tablero() {};

	~Tablero() {};

	//Construye un tablero dada una matriz de NxN bloques. 
	Tablero (Matriz<int> bloques);
	
	//Retorna el numero de bloques fuera de lugar 
	nat PrioridadA();
	
	//Retorna la suma de distancias de los bloques a su posicion final. 
	nat PrioridadB();
	
	//Decide si esta posicion es igual a otra.
	bool operator==(const Tablero& t ) const;

	bool operator!=(const Tablero& t) const;
		
	//Retorna un iterador de las posiciones vecinas a esta. 
	Iterador<Tablero> Vecinos();
	
	//Retorna el tablero. El cero representa la posición libre.
	Matriz<int> ObtenerTablero() const; 

	//Retorna la representación del tablero como cadena.
	Cadena Imprimir() const;
private:
	//Atributos que considre necesarios para resolver el problema. 
	Matriz<int> mat;

	Matriz<int> CopiarMatriz(Matriz<int> original) const;
};

#endif