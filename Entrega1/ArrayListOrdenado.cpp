#ifndef ARRAYLISTORDENADO_CPP
#define ARRAYLISTORDENADO_CPP

#include "ArrayListOrdenado.h"


template<class T>
ArrayListOrdenado<T>::ArrayListOrdenado() {
	l = Array<T>();
}

template<class T>
ArrayListOrdenado<T>::~ArrayListOrdenado() {

}

template<class T>
void ArrayListOrdenado<T>::Insertar(const T & e) {
	int length = (int)l.ObtenerLargo();
	if (length != 0) {
		Array<T> arr = Array<T>(length + 1);
		bool added = false;
		int j = 0;
		for (int i = 0; i < length; i++) {
			if (!added && e < l[i]) {
				arr[j] = e;
				i--;
				added = true;
			} else {
				arr[j] = l[i];
			}
			j++;
		}
		if (!added) {
			arr[arr.ObtenerLargo() - 1] = e;
		}
		l = arr;
	} else {
		l = Array<T>(1);
		l[0] = e;
	}

}

template<class T>
const T & ArrayListOrdenado<T>::Cabeza() {
	return l[0];
}

template<class T>
void ArrayListOrdenado<T>::Eliminar(const T & e) {
	int ocurrencias = 0;
	for (int i = 0; i < (int)l.ObtenerLargo(); i++) {
		if (l[i] == e)
			ocurrencias++;
	}
	int j = 0;
	Array<T> arr = Array<T>(l.ObtenerLargo() - ocurrencias);
	for (int i = 0; i < (int)l.ObtenerLargo(); i++) {
		if (l[i] != e) {
			arr[j] = l[i];
			j++;
		}
	}
	l = arr;
}

template<class T>
Natural ArrayListOrdenado<T>::Largo() const {
	return l.ObtenerLargo();
}

template<class T>
const T & ArrayListOrdenado<T>::Obtener(const Natural n) const{
	assert(n < l.ObtenerLargo());
	return l[n];
}

template<class T>
bool ArrayListOrdenado<T>::Pertenece(const T & e) {
	for (int i = 0; i < (int)l.ObtenerLargo(); i++) {
		if (l[i] == e)
			return true;
	}
	return false;
}

template<class T>
bool ArrayListOrdenado<T>::EstaVacia() const {
	return l.ObtenerLargo() == 0;
}

template<class T>
Puntero<Lista<T>> ArrayListOrdenado<T>::Clon() const {
	Puntero<Lista<T>> lClon = new ArrayListOrdenado<T>();
	for (int i = 0; i < (int)l.ObtenerLargo(); i++) {
		lClon->Insertar(l[i]);
	}
	return lClon;
}

template<class T>
Iterador<T> ArrayListOrdenado<T>::ObtenerIterador() const {
	//class IteradorListaArrayOrdenado : public Iteracion<T> {
	//public:
	//	IteradorListaArrayOrdenado(Array<T> l&) : arr = l, pos = 0{};
	//	void Reiniciar() { pos = 0; };
	//	bool HayElemento() const { return pos != (int)arr.ObtenerLargo(); }
	//	const T& ElementoActual() const { return arr[pos]; };
	//	void Avanzar() const { pos++; };
	//	Puntero<Iteracion<T>> Clon() const { return Puntero<Iteracion<T>>(); };
	//private:
	//	Array<T> arr;
	//	int pos;
	//} it(l);
	return Iterador<T>();
}

#endif // !ARRAYLISTORDENADO_CPP
