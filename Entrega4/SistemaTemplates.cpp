#ifndef SISTEMATEMPLATES_CPP
#define SISTEMATEMPLATES_CPP

#include "Sistema.h"
#include "GrafoMatriz.h"
#include "LinkedList.h"
#include "ColaDePrioridadHeap.h"
#include "Costo.h"

template<class V>
bool Pertenece(Array<V> arr, const V & v, int last) {
	for (int i = 0; i < last; i++) {
		if (arr[i] == v)
			return true;
	}
	return false;
}

template <class V, class A>
Tupla<TipoRetorno, Puntero<Grafo<V, A>>> Sistema::CrearGrafo(nat maxVertices, Puntero<FuncionHash<V>> funcionHash, const Comparador<V>& comp) {
	return Tupla<TipoRetorno, Puntero<Grafo<V, A>>>(OK, new GrafoMatriz<V, A>(maxVertices, funcionHash, comp));
}

template <class V, class A>
bool HayCaminoRec(Puntero<Grafo<V, A>> g, Iterador<V> adyacentes, const V& vD, Puntero<LinkedList<V>> conocidos) {
	if (!adyacentes.HayElemento()) return false;
	V actual = adyacentes.ElementoActual();
	adyacentes.Avanzar();
	if (actual == vD) return true;
	if (conocidos->IndexOf(actual) == -1) { // no es conocido
		conocidos->AddFirst(actual);
		return HayCaminoRec(g, g->Adyacentes(actual), vD, conocidos) || HayCaminoRec(g, adyacentes, vD, conocidos);
	} else {
		return HayCaminoRec(g, adyacentes, vD, conocidos);
	}
}

template <class V, class A>
bool Sistema::HayCamino(Puntero<Grafo<V, A>> g, const V& vO, const V& vD) const {
	auto it = g->Adyacentes(vO);
	Puntero<LinkedList<V>> l = new LinkedList<V>();
	return HayCaminoRec(g, it, vD, l);
}

template <class V, class A>
TipoConexo Sistema::EsConexo(Puntero<Grafo<V, A>> g) const {
	if (Conexo(g))
		return FUERTEMENTE_CONEXO;
	auto gNoDirigido = g->Clon();
	aNoDirigido(gNoDirigido);
	if (Conexo(gNoDirigido))
		return DEBILMENTE_CONEXO;
	return NO_CONEXO;
}

template <class V, class A>
Iterador<V> Sistema::OrdenTopologico(Puntero<Grafo<V, A>> g) const {
	Puntero<LinkedList<V>> l = new LinkedList<V>();
	V v;
	bool hay = VerticeGrado0(g, v);
	while (hay) {
		l->AddLast(v);
		g->BorrarVertice(v);
		hay = VerticeGrado0(g, v);
	}
	return l->GetIterator();
}

template <class V>
bool EsConocido(Array<Tupla<V, Costo, bool, V>> arr, V v) {
	for (int i = 0; i < (int)arr.Largo; i++) {
		if (arr[i].Dato1 == v) {
			return arr[i].Dato3;
		}
	}
	assert(false);
	return false;
}

template <class V>
int IndexOf(Array<Tupla<V, Costo, bool, V>> arr, V v) {
	for (int i = 0; i < (int)arr.Largo; i++) {
		if (arr[i].Dato1 == v) {
			return i;
		}
	}
	assert(false);
	return 0;
}

template <class V>
Puntero<LinkedList<int>> IndexOfHasThisLast(Array<Tupla<V, Costo, bool, V>> arr, V v) {
	Puntero<LinkedList<int>> l = new LinkedList<int>();
	for (int i = 0; i < (int)arr.Largo; i++) {
		if (arr[i].Dato4 == v) {
			l->AddFirst(i);
		}
	}
	return l;
}

template <class V, class A, typename Functor>
Iterador<Tupla<V, V>> Sistema::ArbolCubrimientoMinimo(Puntero<Grafo<V, A>> g, Functor f) const {
	Costo MAX_COST = Costo(Tupla<int, int, int>(INT_MAX, INT_MAX, INT_MAX));
	int vertices = g->CantidadVertices();
	Array<Tupla<V, Costo, bool, V>> arr(vertices);
	auto it = g->Vertices();
	int i = 0;
	Puntero<ColaDePrioridad<V, Costo>> cola = new ColaDePrioridad<V, Costo>(vertices);
	Puntero<LinkedList<Tupla<V, V>>> l = new LinkedList < Tupla<V, V>>();
	while (it.HayElemento()) {
		V v = it.ElementoActual();
		arr[i].Dato1 = v;
		arr[i].Dato2 = MAX_COST;
		arr[i].Dato3 = false;
		i++;
		it.Avanzar();
	}
	arr[0].Dato2 = Costo(Tupla<int,int,int>(0, 0, 0));
	arr[0].Dato3 = true;
	cola->Encolar(arr[0].Dato1, arr[0].Dato2);
	bool first = true;
	while (!cola->IsEmpty()) {
		V v = cola->Desencolar();
		int index = IndexOf(arr, v);
		if (!first) {
			l->AddLast(Tupla<V, V>(arr[index].Dato4, v));
		}
		first = false;
		arr[index].Dato3 = true;
		it = g->Adyacentes(v);
		while (it.HayElemento()) {
			V elem = it.ElementoActual();
			if (!EsConocido(arr, elem)) {
				int index2 = IndexOf(arr, elem);
				Costo cost = f(g->ObtenerArco(v, elem));
				if (cost < arr[index2].Dato2) {
					cola->Encolar(elem, cost);
					arr[index2].Dato2 = cost;
					arr[index2].Dato4 = v;
				}
			}
			it.Avanzar();
		}
	}
	return l->GetIterator();
}

template <class V, class A>
Iterador<Iterador<V>> Sistema::ComponentesConexas(Puntero<Grafo<V, A>> g) const {
	new Iterador<Iterador<V>>();
}

template<class V, class A>
void Sistema::aNoDirigido(Puntero<Grafo<V, A>> g) const {
	auto it = g->Vertices();
	while (it.HayElemento()) {
		auto it2 = g->Vertices();
		while (it2.HayElemento()) {
			V v1 = it.ElementoActual();
			V v2 = it2.ElementoActual();
			if (g->ExisteArco(v1, v2) && !g->ExisteArco(v2, v1)) {
				g->AgregarArco(v2, v1, g->ObtenerArco(v1, v2));
			}
			it2.Avanzar();
		}
		it.Avanzar();
	}
}

template<class V, class A>
bool Sistema::VerticeGrado0(Puntero<Grafo<V, A>> g, V & v) const {
	auto it = g->Vertices();
	while (it.HayElemento()) {
		V elem = it.ElementoActual();
		auto incidentes = g->Incidentes(elem);
		if (!incidentes.HayElemento()) {
			v = elem;
			return true;
		}
		it.Avanzar();
	}
	return false;
}

template<class V, class A>
bool Sistema::Conexo(Puntero<Grafo<V, A>> g) const {
	auto it = g->Vertices();
	while (it.HayElemento()) {
		auto it2 = g->Vertices();
		V v1 = it.ElementoActual();
		while (it2.HayElemento()) {
			V v2 = it2.ElementoActual();
			if (v1 != v2) {
				if (!HayCamino(g, v1, v2))
					return false;
			}
			it2.Avanzar();
		}
		it.Avanzar();
	}
	return true;
}


#endif