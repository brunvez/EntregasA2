#pragma once

#ifndef COLAPRIORIDAD_H
#define COLAPRIORIDAD_H

#include "Iterable.h"
#include "Puntero.h"

typedef unsigned int Natural;

template <class T, class P>
class ColaPrioridad abstract : public Iterable<T>
{
public:
	virtual ~ColaPrioridad() {}

	// PRE: -
	// POS: Encola el elemento e con prioridad p
	virtual void Encolar(const T& e, const P& p) abstract;

	// PRE: La cola no está vacía
	// POS: Retorna el elemento de mayor prioridad en la cola eliminándolo
	virtual const T& Desencolar() abstract;

	// PRE: La cola no está vacía
	// POS: Retorna el elemento de mayor prioridad en la cola sin eliminarlo
	virtual const T& Cabeza() abstract;

	// PRE: -
	// POS: Retorna el largo de la cola
	virtual Natural Largo() const abstract;

	// PRE: El elemento e está en la cola
	// POS: Retorna la instancia del elemento de mayor prioridad dentro de la cola.
	virtual const T& ObtenerPrioridad(const T& e) abstract;

	// PRE: -
	// POS: Retorna true si y solo si el elemento e pertenece a la cola.
	virtual bool Pertenece(const T& e) abstract;

	// PRE: -
	// POS: Retorna true si y solo si la cola esta vacia
	virtual bool EstaVacia() const abstract;

	// PRE: -
	// POS: Retorna true si y solo si la cola esta llena
	virtual bool EstaLlena() const abstract;

	// PRE: -
	// POS: Retorna un clon de la cola que no comparte memoria con ella
	virtual Puntero<ColaPrioridad<T, P>> Clon() const abstract;
};


#endif