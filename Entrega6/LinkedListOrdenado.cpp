#include "LinkedListOrdenado.h"
#include "Array.h"

#ifndef LINKEDLISTORDENADO_CPP
#define LINKEDLISTORDENADO_CPP

template <class T>
LinkedListOrdenado<T>::LinkedListOrdenado() {
	l = NULL;
	length = 0;
}

template <class T>
LinkedListOrdenado<T>::~LinkedListOrdenado() {
	while (l) {
		NodoLista<T> * aux = l;
		l = l->sig;
		delete aux;
	}
}

template<class T>
void LinkedListOrdenado<T>::Insertar(const T & e) {
	if (l) {
		if (l->dato > e) {
			l = new NodoLista<T>(e,l);
		} else {
			NodoLista<T> * frst = l;
			bool added = false;
			while (l) {
				if (e < l->dato) {
					l = new NodoLista<T>(e, l);
					added = true;
					break;
				}
				l = l->sig;
			}
			if (!added)
				l = new NodoLista<T>(e);//Ver como se comporta al agregar al final
			l = frst;
		}
	} else {
		l = new NodoLista<T>(e);
	}
	
	length++;
}

template<class T>
const T & LinkedListOrdenado<T>::Cabeza() {
	assert(l);
	return l->dato;
}

template<class T>
void LinkedListOrdenado<T>::Eliminar(const T & e) {//ver como se comporta al eliminar el primero
	if (l) {
		if (l->dato < e) {
			NodoLista<T> * aux = l;
			while (aux && aux->dato <= e) {
				if (aux->dato == e) {
					NodoLista<T> * d = aux;
					aux = aux->sig;
					length--;
					delete d;
					continue;
				}
				aux = aux->sig;
			}
		} else if (l->dato == e) {
			while (l && l->dato == e) {
				NodoLista<T> * d = l;
				l = l->sig;
				length--;
				delete d;
			}
		}
	}
}

template<class T>
Natural LinkedListOrdenado<T>::Largo() const {
	return length;
}

template<class T>
const T & LinkedListOrdenado<T>::Obtener(const Natural n) const{
	NodoLista<T> * aux = l;
	int i = 0;
	while (n != i) {
		aux = aux->sig;
		i++;
	}
	return aux->dato;
}

template<class T>
bool LinkedListOrdenado<T>::Pertenece(const T & e) {
	NodoLista<T> * aux = l;
	while (aux) {
		if (aux->dato == e) {
			return true;
		}
		aux = aux->sig;
	}
	return false;
}

template<class T>
bool LinkedListOrdenado<T>::EstaVacia() const {
	return length == 0;
}

template<class T>
Puntero<Lista<T>> LinkedListOrdenado<T>::Clon() const {
	Lista<T> * lRet = new LinkedListOrdenado<T>();
	NodoLista<T> * aux = l;
	while (aux) {
		lRet->Insertar(aux->dato);
		aux = aux->sig;
	}
	return Puntero<Lista<T>>(lRet);
}

template<class T>
Iterador<T> LinkedListOrdenado<T>::ObtenerIterador() const {
	Array<T> arr(length);
	NodoLista<T>* aux = l;
	int i = 0;
	while (aux) {
		arr[i++] = aux->dato;
		aux = aux->sig;
	}
	return arr.ObtenerIterador();
}

#endif // LINKEDLISTORDENADO_CPP


