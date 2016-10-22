
#ifndef TABLAHASHABIERTO_H
#define TABLAHASHABIERTO_H
#include "Tabla.h"
#include "Tupla.h"
#include "Puntero.h"
#include "Array.h"
#include "FuncionHash.h"

template<class T, class P>
struct NodoListaDD {
	T key;
	P value;
	Puntero<NodoListaDD<T, P>> sig;
	NodoListaDD(const T& e, const P& p, Puntero<NodoListaDD<T, P>> s = NULL) { key = e; value = p; sig = s; }
};

template <class C, class V>
class TablaHashAbierto :
	public Tabla<C,V> {
public:
	TablaHashAbierto(int size, const Puntero<FuncionHash<C>>& fHash, const Comparador<C>& comp);
	//PRE: T(c) no está definida y la tabla no está llena
	//POS: Define T(c) = v
	void Agregar(const C& c, const V& v);

	//PRE: T(c) está definida
	//POS: Borra la asociación ligada a 'c'
	void Borrar(const C& c);

	//PRE: - 
	//POS: Borra todas las asociaciones
	void BorrarTodos();

	/* PREDICADOS */

	//PRE: - 
	//POS: Retorna true si está vacía, false sino.
	bool EstaVacia() const;

	//PRE: - 
	//POS: Retorna true si está llena, false sino.
	bool EstaLlena() const;

	//PRE: - 
	//POS: Retorna true si T(c) está definida, es decir, si la clave c está definida. False sino.
	bool EstaDefinida(const C& c) const;

	/* SELECTORAS */

	//PRE: T(c) está definida
	//POS: Retorna 'v', tal que T(c) = v
	const V& Obtener(const C& c) const;

	//PRE: -
	//POS: Retorna el largo de la tabla
	nat Largo() const;

	//PRE: -
	//POS: Devuelve un clon de la tabla, no comparten memoria
	Puntero<Tabla<C, V>> Clonar() const;

	Iterador<Tupla<C, V>> ObtenerIterador() const;
private:

	Array<Puntero<NodoListaDD<C, V>>> arr;
	Puntero<FuncionHash<C>> fH;
	Comparador<C> comp;
	int elementos;
};

#include "TablaHashAbierto.cpp"
#endif
