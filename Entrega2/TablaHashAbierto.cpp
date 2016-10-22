#ifndef TABLAHASHABIERTO_CPP
#define TABLAHASHABIERTO_CPP

#include "TablaHashAbierto.h"
#include "IteradorTablaHashAbierto.h"


template<class C, class V>
TablaHashAbierto<C, V>::TablaHashAbierto(int size, const Puntero<FuncionHash<C>>& fHash, const Comparador<C>& comp) {
	arr = Array<Puntero<NodoListaDD<C, V>>>(size * 2);
	fH = fHash;
	this->comp = comp;
	elementos = 0;
}


template<class C, class V>
void TablaHashAbierto<C, V>::Agregar(const C & c, const V & v) {
	int index = fH->CodigoDeHash(c) % arr.ObtenerLargo();
	arr[index] = new NodoListaDD<C, V>(c, v, arr[index]);
	elementos++;
}

template<class C, class V>
void TablaHashAbierto<C, V>::Borrar(const C & c) {
	assert(EstaDefinida(c));
	int index = fH->CodigoDeHash(c) % arr.ObtenerLargo();
	Puntero<NodoListaDD<C, V>> aux = arr[index];
	if (comp.SonIguales(c, aux->key)) {
		arr[index] = aux->sig;
	} else {
		while (aux->sig) {
			if (comp.SonIguales(c, aux->sig->key)) {
				aux->sig = aux->sig->sig;
				break;
			}
			aux = aux->sig;
		}
	}
	elementos--;
}

template<class C, class V>
void TablaHashAbierto<C, V>::BorrarTodos() {
	arr = Array<Puntero<NodoListaDD<C, V>>>(arr.ObtenerLargo());
	elementos = 0;
}

template<class C, class V>
bool TablaHashAbierto<C, V>::EstaVacia() const {
	return elementos == 0;
}

template<class C, class V>
bool TablaHashAbierto<C, V>::EstaLlena() const {
	return false;
}

template<class C, class V>
bool TablaHashAbierto<C, V>::EstaDefinida(const C & c) const {
	int index = fH->CodigoDeHash(c) % arr.ObtenerLargo();
	Puntero<NodoListaDD<C, V>> aux = arr[index];
	while (aux) {
		if (comp.SonIguales(c, aux->key))
			return true;
		aux = aux->sig;
	}
	return false;
}

template<class C, class V>
const V & TablaHashAbierto<C, V>::Obtener(const C & c) const {
	assert(EstaDefinida(c));
	int index = fH->CodigoDeHash(c) % arr.ObtenerLargo();
	Puntero<NodoListaDD<C, V>> aux = arr[index];
	while (aux) {
		C k = aux->key;
		if (comp.SonIguales(c, aux->key))
			return aux->value;
		aux = aux->sig;
	}
	assert(false);
	return aux->value;
}

template<class C, class V>
nat TablaHashAbierto<C, V>::Largo() const {
	return elementos;
}

template<class C, class V>
Puntero<Tabla<C, V>> TablaHashAbierto<C, V>::Clonar() const {
	Puntero<Tabla<C, V>> p = new TablaHashAbierto(arr.ObtenerLargo() / 2, fH, comp);
	for (int i = 0; i < (int)arr.ObtenerLargo(); i++) {
		Puntero<NodoListaDD<C, V>> aux = arr[i];
		while (aux) {
			p->Agregar(aux->key, aux->value);
			aux = aux->sig;
		}
	}
	return p;
}

template<class C, class V>
Iterador<Tupla<C, V>> TablaHashAbierto<C, V>::ObtenerIterador() const {
	return new IteradorTablaHashAbierto<C, V>(arr);
	return Iterador<Tupla<C, V>>();
}

#endif