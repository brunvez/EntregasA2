#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"
#include "Array.h"
#include "Matriz.h"
#include "FuncionHash.h"
#include "Comparador.h"
#include "TablaHashCerrado.h"
#include "Puntero.h"

template <class V, class A>
class GrafoMatriz : public Grafo<V, A> {
public:
	GrafoMatriz(int maxVertices, Puntero<FuncionHash<V>> funcionHash, const Comparador<V>& comp);
	void AgregarVertice(const V& v);
	void BorrarVertice(const V& v);
	void AgregarArco(const V& v1, const V& v2, const A& arco);
	void BorrarArco(const V& v1, const V& v2);

	Iterador<V> Vertices() const;
	Iterador<Tupla<V,A,V>> Aristas() const;
	Iterador<V> Adyacentes(const V& v) const;
	Iterador<V> Incidentes(const V& v) const;

	const A& ObtenerArco(const V& v1, const V& v2) const;
	nat CantidadVertices() const;
	nat CantidadArcos() const;
	nat CantidadAdyacentes(const V& v) const;
	nat CantidadIncidentes(const V& v) const;

	bool ExisteVertice(const V& v) const;
	bool ExisteArco(const V& v1, const V& v2) const;
	bool EstaLleno() const;
	bool EstaVacio() const;

	Puntero<Grafo<V, A>> Clon() const;
private:
	Puntero<Tabla<V, int>> posicionesVertices;
	int posActual;
	int elementos;
	Array<Tupla<V, bool>> vertices;
	Matriz<Tupla<A, bool>> aristas;
	Puntero<FuncionHash<V>> fHash;
	Comparador<V> comp;
};

#include "GrafoMatriz.cpp"
#endif
