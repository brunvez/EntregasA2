#ifndef ARRAYLISTORDENADO_H
#define ARRAYLISTORDENADO_H
#include "Lista.h"
#include "Array.h"

template <class T>
class ArrayListOrdenado :
	public Lista<T> {
public:
	ArrayListOrdenado();
	~ArrayListOrdenado();

	// PRE: -
	// POS: Inserta el elemento
	void Insertar(const T& e);

	// PRE: La lista no está vacía
	// POS: Retorna el primer elemento de la lista
	const T& Cabeza() ;

	// PRE: -
	// POS: Elimina el elemento de la lista si existe. De no existir no tiene acción.
	void Eliminar(const T& e) ;

	// PRE: -
	// POS: Retorna el largo de la lista
	Natural Largo() const ;

	// PRE: La lista tiene un elemento en la posición n. 
	// POS: Retorna el elemento que está en esa posición de la lista. El primer elemento empieza en 0.
	const T& Obtener(const Natural n) const;

	// PRE: -
	// POS: Retorna true si y solo si el elemento e pertenece a la lista.
	bool Pertenece(const T& e) ;

	// PRE: -
	// POS: Retorna true si y solo si la lista esta vacia
	bool EstaVacia() const ;

	// PRE: -
	// POS: Retorna un clon de la lista que no comparte memoria con ella
	Puntero<Lista<T>> Clon() const ;

	Iterador<T> ObtenerIterador() const;
private:
	Array<T> l;
};

#include "ArrayListOrdenado.cpp"
#endif // !ARRAYLISTORDENADO_H
