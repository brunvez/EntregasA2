#ifndef ITERADORTABLAHASHABIERTO_H
#define ITERADORTABLAHASHABIERTO_H
#include "Iteracion.h"
#include "Array.h"

template <class C,class V>
class IteradorTablaHashAbierto: public Iteracion<Tupla<C,V>> {
public:
	IteradorTablaHashAbierto(Array<Puntero<NodoListaDD<C, V>>> arr) {
		for (int i = 0; i < (int)arr.ObtenerLargo(); i++) {
			Puntero<NodoListaDD<C, V>> aux = arr[i];
			while (aux) {
				if (!ppio) {
					ppio = new NodoLista<C, V>(aux->key, aux->value);
					actual = ppio;
				} else {
					actual->sig = new NodoLista<C, V>(aux->key, aux->value);
					actual = actual->sig;
				}
				aux = aux->sig;
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
		NodoLista(const C& key, const V& value, Puntero<NodoLista<C,V>> s = NULL) { dato = Tupla<C,V>(key,value); sig = s; }
	};
	Puntero<NodoLista<C, V>> ppio;
	Puntero<NodoLista<C, V>> actual;

};

#endif