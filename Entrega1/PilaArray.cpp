#ifndef PILAARRAY_CPP
#define PILAARRAY_CPP

#include "PilaArray.h"

template<class T>
PilaArray<T>::PilaArray(int size) {
	arr = Array<T>(size);
	pos = -1;
}

template<class T>
PilaArray<T>::~PilaArray() {
}

template<class T>
void PilaArray<T>::Push(const T & e) {
	if (!EstaLlena()) {
		pos++;
		arr[pos] = e;
	}
}

template<class T>
const T & PilaArray<T>::Top() {
	assert(!EstaVacia());
	return arr[pos];
}

template<class T>
void PilaArray<T>::Pop() {
	pos--;
}

template<class T>
bool PilaArray<T>::EstaLlena() const {
	return pos == (int) arr.ObtenerLargo() - 1;
}

template<class T>
bool PilaArray<T>::EstaVacia() const {
	return pos == -1;
}

template<class T>
Puntero<Pila<T>> PilaArray<T>::Clon() const {
	Pila<T>* p = new PilaArray<T>(arr.ObtenerLargo());
	Puntero<Pila<T>> aux = Puntero<Pila<T>>(p);
	for (int i = 0; i <= pos; i++) {
		aux->Push(arr[i]);
	}
	return aux;
}

template<class T>
Iterador<T> PilaArray<T>::ObtenerIterador() const{
	return Iterador<T>(); // hacer
}


#endif // !PILAARRAT_CPP