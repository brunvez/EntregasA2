#ifndef GRAFO_H
#define GRAFO_H

#include "Iterable.h"
#include "FuncionHash.h"
#include "FuncionCosto.h"
#include "Tupla.h"
#include "Array.h"
#include "Puntero.h"

enum TipoConexo {
	NO_CONEXO, DEBILMENTE_CONEXO, FUERTEMENTE_CONEXO
};

typedef unsigned int nat;

template <class V, class A>
class Grafo abstract {
public:
	// CONSTRUCTORAS

	virtual void AgregarVertice(const V& v) abstract;
	virtual void BorrarVertice(const V& v) abstract;
	virtual void AgregarArco(const V& v1, const V& v2, const A& arco) abstract;
	virtual void BorrarArco(const V& v1, const V& v2) abstract;

	// SELECTORAS y PREDICADOS

	virtual Iterador<V> Vertices() const abstract;
	virtual Iterador<Tupla<V, A, V>> Aristas() const abstract;
	virtual Iterador<V> Adyacentes(const V& v) const abstract;
	virtual Iterador<V> Incidentes(const V& v) const abstract;

	virtual const A& ObtenerArco(const V& v1, const V& v2) const abstract;
	virtual nat CantidadVertices() const abstract;
	virtual nat CantidadArcos() const abstract;
	virtual nat CantidadAdyacentes(const V& v) const abstract;
	virtual nat CantidadIncidentes(const V& v) const abstract;

	virtual bool ExisteVertice(const V& v) const abstract;
	virtual bool ExisteArco(const V& v1, const V& v2) const abstract;
	virtual bool EstaLleno() const abstract;
	virtual bool EstaVacio() const abstract;

	virtual Puntero<Grafo<V, A>> Clon() const abstract;
};

#endif