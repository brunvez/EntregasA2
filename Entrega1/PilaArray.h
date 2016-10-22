#ifndef PILAARRAY_H
#define PILAARRAY_H

#include "Pila.h"
#include "Array.h"

template <class T>
class PilaArray : public Pila<T> {
public:
	PilaArray(int size);
	~PilaArray();

	// Coloca el elemento e en el tope
	void Push(const T& e);

	// Retorna el tope de la pila
	const T& Top();

	// Borra el tope de la pila
	void Pop();

	// PREDICADOS

	// Retorna true si y solo si la lista esta llena
	bool EstaLlena() const;

	// Retorna true si y solo si la lista esta vacia
	bool EstaVacia() const;

	//Retorna un clon de la pila que no comparte memoria con ella
	Puntero<Pila<T>> Clon() const;

	Iterador<T> ObtenerIterador() const;
private:
	Array<T> arr;
	int pos;
};

#include "PilaArray.cpp"
#endif