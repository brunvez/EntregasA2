#ifndef TABLAHASHCERRADO_H
#define TABLAHASHCERRADO_H
#include "Tabla.h"
#include "Tupla.h"
#include "Array.h"
#include "FuncionHash.h"
#include "IteradorHashCerrado.h"


template <class C, class V>
class TablaHashCerrado :
	public Tabla<C,V> {
public:
	TablaHashCerrado(int cubetas, const Puntero<FuncionHash<C>>& fHash, const Comparador<C>& comp);
	~TablaHashCerrado() {};

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
	int repos(int i) const { return (i + 1)*(i + 1) % arr.ObtenerLargo(); }
	Array<Puntero<Tupla<C, V, EstadosHash>>> arr;
	Puntero<FuncionHash<C>> fH;
	Comparador<C> comp;
	int elementos;
};

#include "TablaHashCerrado.cpp"
#endif