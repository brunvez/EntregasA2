#ifndef PILAENCADENADA_CPP
#define PILAENCADENADA_CPP

#include "PilaEncadenada.h"


template<class T>
PilaEncadenada<T>::PilaEncadenada(int size) {
	l = NULL;
	length = 0;
	max = size;
}

template<class T>
PilaEncadenada<T>::~PilaEncadenada() {
	while (l) {
		NodoLista<T> * aux = l;
		l = l->sig;
		delete aux;
	}
}

template<class T>
void PilaEncadenada<T>::Push(const T & e) {
	if (!EstaLlena()) {
		NodoLista<T> * aux = new NodoLista<T>(e, l);
		l = aux;
		length++;
	}
}

template<class T>
const T & PilaEncadenada<T>::Top() {
	assert(!EstaVacia());
	return l->dato;
}

template<class T>
void PilaEncadenada<T>::Pop() {
	NodoLista<T> * aux = l;
	l = l->sig;
	length--;
	delete aux;
}

template<class T>
bool PilaEncadenada<T>::EstaLlena() const {
	return max == length;
}

template<class T>
bool PilaEncadenada<T>::EstaVacia() const {
	return l == NULL;
}

template<class T>
Puntero<Pila<T>> PilaEncadenada<T>::Clon() const {
	Pila<T>* p = new PilaEncadenada<T>(max);
	Puntero<Pila<T>> aux = Puntero<Pila<T>>(p);
	NodoLista<T> *lAux = l;
	while (lAux != NULL) {
		aux->Push(lAux->dato);
		lAux = lAux->sig;
	}
	return aux;
}

template<class T>
Iterador<T> PilaEncadenada<T>::ObtenerIterador() const{
	return Iterador<T>(); //hacer
}

#endif
