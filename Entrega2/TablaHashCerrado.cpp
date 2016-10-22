#ifndef TABLAHASHCERRADO_CPP
#define TABLAHASHCERRADO_CPP
#include "TablaHashCerrado.h"

template<class C, class V>
TablaHashCerrado<C, V>::TablaHashCerrado(int cubetas, const Puntero<FuncionHash<C>>& fHash, const Comparador<C>& comp) {
	arr = Array<Puntero<Tupla<C, V, EstadosHash>>>(cubetas*2);
	fH = fHash;
	this->comp = comp;
	elementos = 0;
}

template<class C, class V>
void TablaHashCerrado<C, V>::Agregar(const C & c, const V & v) {
	assert(!EstaLlena());
	int pos = fH->CodigoDeHash(c) % arr.ObtenerLargo();
	while (arr[pos] != NULL && arr[pos]->Dato3 != OCUPADO) {
		pos = repos(pos);
	}
	arr[pos] = new Tupla<C, V, EstadosHash>(c, v, OCUPADO);
	elementos++;
}

template<class C, class V>
void TablaHashCerrado<C, V>::Borrar(const C & c) {
	int pos = fH->CodigoDeHash(c) % arr.ObtenerLargo();
	while (arr[pos] != NULL && !comp.SonIguales(arr[pos]->Dato1, c) && arr[pos]->Dato3 != LIBRE) {
		pos = repos(pos);
	}
	if (arr[pos]->Dato3 != LIBRE && comp.SonIguales(arr[pos]->Dato1, c)) {
		//arr[pos]->Dato1 = C();
		//arr[pos]->Dato1 = V();
		arr[pos]->Dato3 = LIBRE;
		elementos--;
	}

}

template<class C, class V>
void TablaHashCerrado<C, V>::BorrarTodos() {
	for (int i = 0; i < (int)arr.ObtenerLargo(); i++) {
		arr[i] = NULL;
		elementos--;
	}
	elementos = 0;
}

template<class C, class V>
bool TablaHashCerrado<C, V>::EstaVacia() const {
	return elementos == 0;
}

template<class C, class V>
bool TablaHashCerrado<C, V>::EstaLlena() const {
	return elementos == (int) arr.ObtenerLargo();
}

template<class C, class V>
bool TablaHashCerrado<C, V>::EstaDefinida(const C & c) const {
	int pos = fH->CodigoDeHash(c) % arr.ObtenerLargo();
	while (arr[pos] != NULL && (!comp.SonIguales(arr[pos]->Dato1, c) || arr[pos]->Dato3 == LIBRE)) {
		pos = repos(pos);
	}
	if (arr[pos] != NULL && arr[pos]->Dato3 != LIBRE && comp.SonIguales(arr[pos]->Dato1, c)) {
		return true;
	}
	return false;
}

template<class C, class V>
const V & TablaHashCerrado<C, V>::Obtener(const C & c) const {
	int pos = fH->CodigoDeHash(c) % arr.ObtenerLargo();
	while (arr[pos] != NULL && (!comp.SonIguales(arr[pos]->Dato1, c) || arr[pos]->Dato3 == LIBRE)) {
		pos = repos(pos);
	}
		return arr[pos]->Dato2;
}

template<class C, class V>
nat TablaHashCerrado<C, V>::Largo() const {
	return elementos;
}

template<class C, class V>
Puntero<Tabla<C, V>> TablaHashCerrado<C, V>::Clonar() const {
	Puntero<Tabla<C, V>> p = new TablaHashCerrado<C,V>(arr.ObtenerLargo() / 2, fH, comp);
	for (int i = 0; i < (int)arr.ObtenerLargo(); i++) {
		if (arr[i] != NULL && arr[i]->Dato3 != LIBRE) {//se muere todo si no mando los libres...mando y elimino?
			p->Agregar(arr[i]->Dato1, arr[i]->Dato2);
		}
	}
	return p;
}

template<class C, class V>
Iterador<Tupla<C, V>> TablaHashCerrado<C, V>::ObtenerIterador() const {
	return new IteradorTablaHashCerrado<C,V>(arr);
}

#endif // !TABLAHASHCERRADO_CPP

