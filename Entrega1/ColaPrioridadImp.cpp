#ifndef COLAPRIORIDADIMP_CPP
#define COLAPRIORIDADIMP_CPP

#include "ColaPrioridadImp.h"


template <class T, class P>
ColaPrioridadImp<T, P>::ColaPrioridadImp(int size) {
	l = NULL;
	length = 0;
	max = size;
}

template <class T, class P>
ColaPrioridadImp<T, P>::~ColaPrioridadImp() {
	while (l) {
		NodoListaDD<T, P> * aux = l;
		l = l->sig;
		delete aux;
	}
}
template<class T, class P>
void ColaPrioridadImp<T, P>::Encolar(const T & e, const P & p) {
	if (EstaLlena()) {
		int i = 1;
		NodoListaDD<T, P> * frst = l;
		while (l) {
			i++;
			if (i >= max) {
				NodoListaDD<T, P> * d = l->sig;
				l->sig = NULL;
				length--;
				delete d;
				break;
			}
			l = l->sig;
		}
		l = frst;
	}

	if (l) {
		if (l->prio <= p) {
			l = new NodoListaDD<T, P>(e, p, l);
		} else {
			NodoListaDD<T, P> * frst = l;
			bool added = false;
			while (l->sig) {
				if (p >= l->sig->prio) {
					l->sig = new NodoListaDD<T, P>(e, p,l->sig);
					added = true;
					break;
				}
				l = l->sig;
			}
			l = frst;
			if (!added) { // ver como se comporta al agregar ultimo
				while (l->sig) {
					l = l->sig;
				}
				l->sig = new NodoListaDD<T, P>(e, p);
			}
			l = frst;
		}
	} else {
		l = new NodoListaDD<T, P>(e, p);
	}
	length++;
}

template<class T, class P>
const T & ColaPrioridadImp<T, P>::Desencolar() {
	assert(!EstaVacia());
	NodoListaDD<T, P> *d = l;
	T &t = *(new T(l->dato));
	l = l->sig;
	length--;
	delete d;
	return t;
}

template<class T, class P>
const T & ColaPrioridadImp<T, P>::Cabeza() {
	return l->dato;
}

template<class T, class P>
Natural ColaPrioridadImp<T, P>::Largo() const {
	return length;
}

template<class T, class P>
const T & ColaPrioridadImp<T, P>::ObtenerPrioridad(const T & e) {
	assert(Pertenece(e));
	NodoListaDD<T, P> * aux = l;
	while (aux) {
		if (aux->dato == e)
			return aux->dato;
	}
	assert(false);
	return l->dato;
}

template<class T, class P>
bool ColaPrioridadImp<T, P>::Pertenece(const T & e) {
	NodoListaDD<T, P> * aux = l;
	while (aux) {
		if (aux->dato == e)
			return true;
	}
	return false;
}

template<class T, class P>
bool ColaPrioridadImp<T, P>::EstaVacia() const {
	return length == 0;
}

template<class T, class P>
bool ColaPrioridadImp<T, P>::EstaLlena() const {
	return length == max;
}

template<class T, class P>
Puntero<ColaPrioridad<T, P>> ColaPrioridadImp<T, P>::Clon() const {
	ColaPrioridad<T, P> * c = new ColaPrioridadImp<T, P>(max);
	NodoListaDD<T, P> * frst = l;
	while (frst) {
		c->Encolar(frst->dato, frst->prio);
		frst = frst->sig;
	}
	return Puntero<ColaPrioridad<T, P>>(c);
}

template<class T, class P>
Iterador<T> ColaPrioridadImp<T, P>::ObtenerIterador() const {
	return Iterador<T>();
}
#endif