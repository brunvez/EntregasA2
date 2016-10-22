#ifndef SISTEMA_H
#define SISTEMA_H

#include "Cadena.h"
#include "Puntero.h"
#include "Tupla.h"
#include "NodoArbol.h"
#include "Tabla.h"
#include "FuncionHash.h"
#include "TablaHashAbierto.h"
#include "FuncionHashAnagramas.h"
#include "ComparadorStrings.h"


class Sistema
{
public:
	Sistema();
	~Sistema();

	// Ejercicio 1: Anagramas, TablaHash abierta y cerrada
	Array<Cadena> Anagramas(const Cadena& c);
	
	template <class C, class V>
	Puntero<Tabla<C, V>> CrearTablaHashAbierto(nat cubetas, const Puntero<FuncionHash<C>>& fHash, const Comparador<C>& comp);
	
	template <class C, class V>
	Puntero<Tabla<C, V>> CrearTablaHashCerrado(nat cubetas, const Puntero<FuncionHash<C>>& fHash, const Comparador<C>& comp);

	// Ejercicio 2: AVL
	template <class T>
	bool EsAVL(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp);

private:
	template<class T>
	T min(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp);
	template<class T>
	T max(Puntero<NodoArbol<T>> raiz, const Comparador<T>& comp);
	template<class T>
	T min(T t1, T t2, const Comparador<T>& comp);
	template<class T>
	T max(T t1, T t2, const Comparador<T>& comp);
	string Alphabetize(string str) const;
	template <class T>
	struct NodoLista {
		T dato;
		Puntero<NodoLista<T>> sig;
		NodoLista(const T& d, Puntero<NodoLista<T>> s = NULL) { dato = d; sig = s; }
	};
	Puntero<FuncionHash<string>> fH;
	Puntero<TablaHashAbierto<string, Puntero<NodoLista<string>>>> tabla;
};


#include "SistemaTemplates.cpp"

#endif
