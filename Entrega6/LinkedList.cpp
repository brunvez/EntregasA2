#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP
#include "LinkedList.h"

template<class T>
LinkedList<T>::LinkedList() {
	list = NULL;
	size = 0;
}

template<class T>
void LinkedList<T>::Add(T & e, int index) {
	assert(index <= size);
	assert(index >= 0);
	Add(e, index, list);
	size++;
}

template<class T>
void LinkedList<T>::AddFirst(T & e) {
	Add(e, 0, list);
	size++;
}

template<class T>
void LinkedList<T>::AddLast(T & e) {
	Add(e, size,list);
	size++;
}

template<class T>
void LinkedList<T>::Clear() {
	size = 0;
	list = NULL;
}

template<class T>
bool LinkedList<T>::Contains(const T & e) const {
	return Contains(e, list);
}

template<class T>
T & LinkedList<T>::Get(int index) const {
	assert(index < size);
	assert(index >= 0);
	return Get(index, list);
}

template<class T>
T & LinkedList<T>::GetFirst() const {
	assert(list != NULL);
	return Get(0, list);
}

template<class T>
T & LinkedList<T>::GetLast() const {
	assert(list != NULL);
	return Get(size - 1, list);
}

template<class T>
int LinkedList<T>::IndexOf(const T & e) const {
	return IndexOf(e, list);
}

template<class T>
void LinkedList<T>::Remove(const T & e) {
	if (Remove(e, list))
		size--;
}

template<class T>
void LinkedList<T>::Remove(int index) {
	assert(index < size);
	assert(index >= 0);
	Remove(index, list);
	size--;
}

template<class T>
void LinkedList<T>::RemoveFirst() {
	assert(!IsEmpty());
	Remove(0, list);
}

template<class T>
int LinkedList<T>::Size() const {
	return size;
}

template<class T>
bool LinkedList<T>::IsEmpty() const {
	return size == 0;
}

template<class T>
Iterador<T> LinkedList<T>::GetIterator() const {
	Array<T> arr = this->ToArray();
	return arr.ObtenerIterador();
}

template<class T>
Array<T> LinkedList<T>::ToArray() const {
	Array<T> arr(size);
	Puntero<NodoLista<T>> aux = list;
	for (int i = 0; i < size; i++) {
		arr[i] = aux->dato;
		aux = aux->sig;
	}
	return arr;
}

template<class T>
void LinkedList<T>::Add(T & e, int index, Puntero<NodoLista<T>> &list) {
	if (index == 0) {
		list = new NodoLista<T>(e, list);
	} else {
		Add(e, index - 1, list->sig);
	}
}

template<class T>
bool LinkedList<T>::Contains(const T & e, Puntero<NodoLista<T>> list) const {
	if (list == NULL) return false;
	return list->dato == e || Contains(e, list->sig);
}

template<class T>
T & LinkedList<T>::Get(int index, Puntero<NodoLista<T>> list) const {
	if (index == 0) {
		return list->dato;
	} else {
		return Get(index - 1, list->sig);
	}
}

template<class T>
int LinkedList<T>::IndexOf(const T & e, Puntero<NodoLista<T>> list) const {
	if (list == NULL) return -1;
	int cont = 0;
	while (list != NULL) {
		if (e == list->dato)
			return cont;
		cont++;
		list = list->sig;
	}
	return -1;
}

template<class T>
bool LinkedList<T>::Remove(const T & e, Puntero<NodoLista<T>> &list) {
	if (list != NULL) {
		if (list->dato == e) {
			list = list->sig;
			return Remove(e, list) || true;
		} else {
			return Remove(e, list->sig);
		}
	} else {
		return false;
	}
}

template<class T>
void LinkedList<T>::Remove(int index, Puntero<NodoLista<T>> &list) {
	if (index == 0) {
		list = list->sig;
	} else {
		Remove(index - 1, list->sig);
	}
}


#endif
