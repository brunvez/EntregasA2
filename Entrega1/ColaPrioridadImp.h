#ifndef COLAPRIORIDADIMP_H
#define COLAPRIORIDADIMP_H

#include "ColaPrioridad.h"
template <class T, class P>
class ColaPrioridadImp :
	public ColaPrioridad<T, P> {
public:
	ColaPrioridadImp(int size);
	~ColaPrioridadImp();


	// PRE: -
	// POS: Encola el elemento e con prioridad p
	void Encolar(const T& e, const P& p);

	// PRE: La cola no está vacía
	// POS: Retorna el elemento de mayor prioridad en la cola eliminándolo
	const T& Desencolar();

	// PRE: La cola no está vacía
	// POS: Retorna el elemento de mayor prioridad en la cola sin eliminarlo
	const T& Cabeza();

	// PRE: -
	// POS: Retorna el largo de la cola
	Natural Largo() const;

	// PRE: El elemento e está en la cola
	// POS: Retorna la instancia del elemento de mayor prioridad dentro de la cola.
	const T& ObtenerPrioridad(const T& e);

	// PRE: -
	// POS: Retorna true si y solo si el elemento e pertenece a la cola.
	bool Pertenece(const T& e);

	// PRE: -
	// POS: Retorna true si y solo si la cola esta vacia
	bool EstaVacia() const;

	// PRE: -
	// POS: Retorna true si y solo si la cola esta llena
	bool EstaLlena() const;

	// PRE: -
	// POS: Retorna un clon de la cola que no comparte memoria con ella
	Puntero<ColaPrioridad<T, P>> Clon() const;

	Iterador<T> ObtenerIterador() const;
private:
	template<class T, class P>
	struct NodoListaDD {
		T dato;
		P prio;
		NodoListaDD<T,P> * sig;
		NodoListaDD(const T& e, const P& p, NodoListaDD<T,P>*s = NULL) { dato = e; prio = p; sig = s; }
	};
	NodoListaDD<T, P> *l;
	int length;
	int max;
};

#include "ColaPrioridadImp.cpp"
#endif