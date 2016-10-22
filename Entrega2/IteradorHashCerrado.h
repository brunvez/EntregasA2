#ifndef ITERADORTABLAHASHCERRADO_H
#define ITERADORTABLAHASHCERRADO_H
#include "Iteracion.h"
#include "Array.h"
#include "Tupla.h"
#include "TablaHashCerrado.h"


enum EstadosHash {
	OCUPADO, LIBRE
};

template <class C, class V>
class IteradorTablaHashCerrado : public Iteracion<Tupla<C, V>> {
public:
	IteradorTablaHashCerrado(Array<Puntero<Tupla<C, V, EstadosHash>>> arr) {
		for (int i = 0; i < (int)arr.ObtenerLargo(); i++) {
			Puntero<Tupla<C, V, EstadosHash>> t = arr[i];
			if(t != NULL && t->Dato3 != LIBRE) {
				if (!ppio) {
					ppio = new NodoLista<C, V>(t->Dato1, t->Dato2);
					actual = ppio;
				} else {
					actual->sig = new NodoLista<C, V>(t->Dato1, t->Dato2);
					actual = actual->sig;
				}
			}
		}
		actual = ppio;
	}

	void Reiniciar() { actual = ppio; };

	bool HayElemento() const { return actual != NULL; };

	const Tupla<C, V>& ElementoActual() const { return actual->dato; };

	void Avanzar() { assert(actual); actual = actual->sig; };

private:
	template <class C, class V>
	struct NodoLista {
		Tupla<C, V> dato;
		Puntero<NodoLista<C, V>> sig;
		NodoLista(const C& key, const V& value, Puntero<NodoLista<C, V>> s = NULL) { dato = Tupla<C, V>(key, value); sig = s; }
	};
	Puntero<NodoLista<C, V>> ppio;
	Puntero<NodoLista<C, V>> actual;

};

#endif