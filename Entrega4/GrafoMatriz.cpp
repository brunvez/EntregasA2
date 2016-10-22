#include "GrafoMatriz.h"
#ifndef GRAFOMATRIZ_CPP
#define GRAFOMATRIZ_CPP
#include "LinkedList.h"

template<class V, class A>
GrafoMatriz<V, A>::GrafoMatriz(int maxVertices, Puntero<FuncionHash<V>> funcionHash, const Comparador<V>& comp) {
	vertices = Array<Tupla<V, bool>>(maxVertices);
	posicionesVertices = new TablaHashCerrado<V, int>(maxVertices, funcionHash, comp);
	posActual = 0;
	elementos = 0;
	aristas = Matriz<Tupla<A, bool>>(maxVertices);
	for (int i = 0; i < maxVertices; i++) {
		vertices[i] = Tupla<V, bool>(V(), false);
		for (int j = 0; j < maxVertices; j++) {
			aristas[i][j] = Tupla<A, bool>(A(), false);
		}
	}
	fHash = funcionHash;
	this->comp = comp;
}

template<class V, class A>
void GrafoMatriz<V, A>::AgregarVertice(const V & v) {
	assert(!EstaLleno());
	int index = posActual++;
	assert(!vertices[index].Dato2); // No hay vertice en esa posicion
	posicionesVertices->Agregar(v, index); // Asigno index a ese vertice
	vertices[index] = Tupla<V, bool>(v, true); // asigno el vertice a index
	elementos++;
	while (posActual < (int)vertices.Largo && vertices[posActual].Dato2) { // encuentro la proxima posicion en el array sin vertice
		posActual++;
	}
};

template<class V, class A>
void GrafoMatriz<V, A>::BorrarVertice(const V & v) {
	int index = posicionesVertices->Obtener(v); // obtengo pos
	assert(comp.SonIguales(vertices[index].Dato1, v)); // que sea ese
	posicionesVertices->Borrar(v); // le saco la pos
	vertices[index].Dato2 = false; // lo 'saco' del array
	posActual = index; // el proximo entra en esa pos
	elementos--; // hay un elemento menos
	for (int i = 0; i < (int)vertices.Largo; i++) { // borro las aristas relacionadas con el
		aristas[i][index].Dato2 = false;
		aristas[index][i].Dato2 = false;
	}
}

template<class V, class A>
void GrafoMatriz<V, A>::AgregarArco(const V & v1, const V & v2, const A & arco) {
	int index1 = posicionesVertices->Obtener(v1);
	int index2 = posicionesVertices->Obtener(v2);
	assert(!vertices[index1].Dato2 || comp.SonIguales(vertices[index1].Dato1, v1));
	vertices[index1] = Tupla<V, bool>(v1, true);
	assert(!vertices[index2].Dato2 || comp.SonIguales(vertices[index2].Dato1, v2));
	vertices[index2] = Tupla<V, bool>(v2, true);
	aristas[index1][index2] = Tupla<A, bool>(arco, true);
}

template<class V, class A>
void GrafoMatriz<V, A>::BorrarArco(const V & v1, const V & v2) {
	int index1 = posicionesVertices->Obtener(v1);
	int index2 = posicionesVertices->Obtener(v2);
	assert(aristas[index1][index2].Dato2);
	aristas[index1][index2].Dato2 = false;
}

template<class V, class A>
Iterador<V> GrafoMatriz<V, A>::Vertices() const {
	Puntero<LinkedList<V>> l = new LinkedList<V>();
	for (int i = 0; i < (int)vertices.Largo; i++) {
		if (vertices[i].Dato2)
			l->AddLast(vertices[i].Dato1);
	}
	return l->GetIterator();
}

template<class V, class A>
Iterador<V> GrafoMatriz<V, A>::Adyacentes(const V & v) const {
	int index = posicionesVertices->Obtener(v);
	Puntero<LinkedList<V>> l = new LinkedList<V>();
	for (int i = 0; i < (int)vertices.Largo; i++) {
		if (aristas[index][i].Dato2) {
			l->AddLast(vertices[i].Dato1);
		}
	}
	return l->GetIterator();
}

template<class V, class A>
Iterador<V> GrafoMatriz<V, A>::Incidentes(const V & v) const {
	int index = posicionesVertices->Obtener(v);
	Puntero<LinkedList<V>> l = new LinkedList<V>();
	for (int i = 0; i < (int)vertices.Largo; i++) {
		if (aristas[i][index].Dato2) {
			l->AddLast(vertices[i].Dato1);
		}
	}
	return l->GetIterator();
}

template<class V, class A>
const A & GrafoMatriz<V, A>::ObtenerArco(const V & v1, const V & v2) const {
	int index1 = posicionesVertices->Obtener(v1);
	int index2 = posicionesVertices->Obtener(v2);
	assert(aristas[index1][index2].Dato2);
	return aristas[index1][index2].Dato1;
}

template<class V, class A>
nat GrafoMatriz<V, A>::CantidadVertices() const {
	int cont = 0;
	for (int i = 0; i < (int)vertices.Largo; i++) {
		if (vertices[i].Dato2)
			cont++;
	}
	return cont;
}

template<class V, class A>
nat GrafoMatriz<V, A>::CantidadArcos() const {
	int cont = 0;
	for (int i = 0; i < (int)vertices.Largo; i++) {
		for (int j = 0; j < (int)vertices.Largo; j++) {
			if (aristas[i][j].Dato2)
				cont++;
		}
	}
	return cont;
}

template<class V, class A>
nat GrafoMatriz<V, A>::CantidadAdyacentes(const V & v) const {
	int cont = 0;
	int index = posicionesVertices->Obtener(v);
	for (int i = 0; i < (int)vertices.Largo; i++) {
		if (aristas[index][i].Dato2) {
			cont++;
		}
	}
	return cont;
}

template<class V, class A>
nat GrafoMatriz<V, A>::CantidadIncidentes(const V & v) const {
	int cont = 0;
	int index = posicionesVertices->Obtener(v);
	for (int i = 0; i < (int)vertices.Largo; i++) {
		if (aristas[i][index].Dato2) {
			cont++;
		}
	}
	return cont;
}

template<class V, class A>
bool GrafoMatriz<V, A>::ExisteVertice(const V & v) const {
	int index = posicionesVertices->Obtener(v);
	return vertices[index].Dato2 && comp.SonIguales(vertices[index].Dato1, v);
}

template<class V, class A>
bool GrafoMatriz<V, A>::ExisteArco(const V & v1, const V & v2) const {
	int index1 = posicionesVertices->Obtener(v1);
	int index2 = posicionesVertices->Obtener(v2);
	return aristas[index1][index2].Dato2;
}

template<class V, class A>
bool GrafoMatriz<V, A>::EstaLleno() const {
	return elementos == (int)vertices.Largo;
}

template<class V, class A>
bool GrafoMatriz<V, A>::EstaVacio() const {
	return elementos == 0;
}

template<class V, class A>
Puntero<Grafo<V, A>> GrafoMatriz<V, A>::Clon() const {
	Grafo<V, A> * g = new GrafoMatriz<V, A>(vertices.Largo, fHash, comp);
	for (int i = 0; i < (int)vertices.Largo; i++) {
		if (vertices[i].Dato2) {
			g->AgregarVertice(vertices[i].Dato1);
		}

	}
	for (int i = 0; i < (int)vertices.Largo; i++) {
		for (int j = 0; j < (int)vertices.Largo; j++) {
			if (aristas[i][j].Dato2) {
				g->AgregarArco(vertices[i].Dato1, vertices[j].Dato1, aristas[i][j].Dato1);
			}
		}
	}

	return g;
}


#endif // !GRAFOMATRIZ_CPP
