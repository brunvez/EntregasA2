#pragma once

#ifndef LISTA_H
#define LISTA_H

#include "Iterable.h"
#include "Puntero.h"

typedef unsigned int Natural;

template <class T>
class Lista abstract : public Iterable<T>
{
public:
	virtual ~Lista() {}

	// PRE: -
	// POS: Inserta el elemento
	virtual void Insertar(const T& e) abstract;

	// PRE: La lista no está vacía
	// POS: Retorna el primer elemento de la lista
	virtual const T& Cabeza() abstract;

	// PRE: -
	// POS: Elimina el elemento de la lista si existe. De no existir no tiene acción.
	virtual void Eliminar(const T& e) abstract;

	// PRE: -
	// POS: Retorna el largo de la lista
	virtual Natural Largo() const abstract;

	// PRE: La lista tiene un elemento en la posición n. 
	// POS: Retorna el elemento que está en esa posición de la lista. El primer elemento empieza en 0.
	virtual const T& Obtener(const Natural n) const abstract;

	// PRE: -
	// POS: Retorna true si y solo si el elemento e pertenece a la lista.
	virtual bool Pertenece(const T& e) abstract;

	// PRE: -
	// POS: Retorna true si y solo si la lista esta vacia
	virtual bool EstaVacia() const abstract;

	// PRE: -
	// POS: Retorna un clon de la lista que no comparte memoria con ella
	virtual Puntero<Lista<T>> Clon() const abstract;
};


#endif