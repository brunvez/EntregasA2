#ifndef SISTEMATEMPLATES_CPP
#define SISTEMATEMPLATES_CPP

#include "Sistema.h"
#include "TablaHashAbierto.h"
#include "TablaHashCerrado.h"

template <class C, class V>
Puntero<Tabla<C, V>> Sistema::CrearTablaHashAbierto(nat cubetas, const Puntero<FuncionHash<C>>& fHash, const Comparador<C>& comp) {
	return new TablaHashAbierto<C, V>(cubetas, fHash, comp);
	return NULL;
}

template <class C, class V>
Puntero<Tabla<C, V>> Sistema::CrearTablaHashCerrado(nat cubetas, const Puntero<FuncionHash<C>>& fHash, const Comparador<C>& comp) {
	return new TablaHashCerrado<C, V>(cubetas, fHash, comp);
	return NULL;
}


template <class T>
int AlturaABB(Puntero<NodoArbol<T>> raiz) {
	if (!raiz) return 0;
	int a = AlturaABB(raiz->izq);
	int b = AlturaABB(raiz->der);
	return 1 + (a < b ? b : a);
}


template <class T>
bool Sistema::EsAVL(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp) {
	if (!raiz) return true;
	int heightI = AlturaABB(raiz->izq);
	int heightD = AlturaABB(raiz->der);
	bool ret = (heightI == heightD || heightI - 1 == heightD || heightI == heightD - 1);
	if (raiz->izq)
		ret &= comp.EsMayor(raiz->dato, max(raiz->izq, comp));
	if (raiz->der)
		ret &= comp.EsMenor(raiz->dato, min(raiz->der, comp));
	ret &= EsAVL(raiz->izq, comp);
	ret &= EsAVL(raiz->der, comp);
	return ret;
}
template<class T>
T Sistema::min(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp) {
	if (!raiz->der && !raiz->izq) 
		return raiz->dato;
	if (!raiz->izq)
		return min(raiz->dato, min(raiz->der, comp), comp);
	if (!raiz->der)
		return min(raiz->dato, min(raiz->izq, comp), comp);
	return min(raiz->dato, min(min(raiz->izq, comp), min(raiz->der, comp),comp), comp);
}

template<class T>
T Sistema::max(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp) {
	if (!raiz->der && !raiz->izq)
		return raiz->dato;
	if (!raiz->izq)
		return max(raiz->dato, max(raiz->der, comp), comp);
	if (!raiz->der)
		return max(raiz->dato, max(raiz->izq, comp), comp);
	return max(raiz->dato, max(max(raiz->izq, comp), max(raiz->der, comp),comp), comp);
}

template<class T>
T Sistema::min(T t1, T t2, const Comparador<T>& comp) {
	return comp.EsMenor(t1, t2) ? t1 : t2;
}

template<class T>
T Sistema::max(T t1, T t2, const Comparador<T>& comp) {
	return comp.EsMayor(t1, t2) ? t1 : t2;
}
#endif