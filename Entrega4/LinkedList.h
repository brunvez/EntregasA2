#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Puntero.h"
#include "Array.h"
#include "Iterador.h"
#include <assert.h>

template <class T>
class LinkedList {
public:
	LinkedList();
	//pre: index <= size
	//pos: inserta un elemento a la lista en esa posicion
	void Add(T& e, int index);
	//pre:
	//pos: inserta un elemento a la lista al principio
	void AddFirst(T& e);
	//pre:
	//pos: inserta un elemento a la lista al final
	void AddLast(T& e);
	//pre:
	//pos: borra todos los elemntos de la lista
	void Clear();
	//pre:
	//pos: retorna true si el elemento esta en la lista
	bool Contains(const T& e) const;
	//pre: index < size
	//pos: retorna el elemento en la posicion
	T& Get(int index) const;
	//pre: !IsEmpty()
	//pos: retorna el primer elemento
	T& GetFirst() const;
	//pre: !IsEmpty()
	//pos: retorna el ultimo elemento
	T& GetLast() const;
	//pre: 
	//pos: retorna la posicion del elemento, -1 si no existe
	int IndexOf(const T& e) const;
	//pre:
	//post: borra todas las ocurrencias de e en la lista
	void Remove(const T& e);
	//pre: 0 <= index < size
	//pos: borra el elemento en la posicion index
	void Remove(int index);
	//pre: !IsEmpty()
	//pos: borra el primer elemento de la lista
	void RemoveFirst();
	//pre:
	//pos: retorna la cantidad de elementos en la lista
	int Size() const;
	//pre:
	//pos: retorna true si no hay elementos en la lista, false en otro caso
	bool IsEmpty() const;
	//pre:
	//pos: retorna un iterador a la lista
	Iterador<T> GetIterator() const;
	//pre:
	//pos: retorna un array con los elementos de la lista
	Array<T> ToArray() const;
private:
	template<class T>
	struct NodoLista {
		T dato;
		Puntero<NodoLista<T>> sig;
		NodoLista(const T& e, Puntero<NodoLista<T>> s = NULL) { dato = e; sig = s; };
	};
	Puntero<NodoLista<T>> list;
	int size;
	//Funciones auxiliares
	void Add(T& e, int index, Puntero<NodoLista<T>> &list);
	bool Contains(const T& e, Puntero<NodoLista<T>> list) const;
	T& Get(int index, Puntero<NodoLista<T>> list) const;
	int IndexOf(const T& e, Puntero<NodoLista<T>> list) const;
	bool Remove(const T& e, Puntero<NodoLista<T>> &list);
	void Remove(int index, Puntero<NodoLista<T>> &list);
};
#include "LinkedList.cpp"
#endif // !LINKEDLIST_H