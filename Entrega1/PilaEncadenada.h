#ifndef PILAENCADENADA_H
#define PILAENCADENADA_H

#include "Pila.h"
#include "Iterable.h"

template <class T>
class PilaEncadenada : public Pila<T> {
public:
	PilaEncadenada(int size);
	~PilaEncadenada();

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
	template<class T>
	struct NodoLista {
		T dato;
		NodoLista<T> * sig;
		NodoLista(const T& e, NodoLista<T>*s = NULL) { dato = e; sig = s; }
	};
	NodoLista<T>* l;
	int length;
	int max;
};

#include "PilaEncadenada.cpp"
#endif // !PILAENCADENADA_CPP
