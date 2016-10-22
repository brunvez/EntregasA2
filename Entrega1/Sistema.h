#ifndef SISTEMA_H
#define SISTEMA_H

#include "Cadena.h"
#include "Iterador.h"
#include "Puntero.h"
#include "Tupla.h"
#include "Pila.h"
#include "Lista.h"
#include "ColaPrioridad.h"

class Sistema
{
public:
	Sistema();
	~Sistema();

	// Ejercicio 1: ordenamiento
	template <class T>
	void merge(Array<T>& arr, int l, int m, int r, const Comparador<T>& comp);
	template <class T>
	void mergeSort(Array<T>& arr, int l, int r, const Comparador<T>& comp);
	template<class T>
	int binarySearch(const Array<T>& arr, const T & value, const Comparador<T>& c, int left, int right);
	template <class T>
	void Ordenar(Array<T>& elementos, const Comparador<T>& comp);
	void OrdenarEnteros(Array<int>& elementos, const Comparador<int>& comp);

	// Operación 2: Búsqueda
	template <class T>
	int Busqueda(const Array<T>& elementos, const T& elem, const Comparador<T>& comp);
	bool ExisteSuma(const Array<int>& elementos, int suma);

	// Operación 3: TAD Pila
	template <class T>
	Puntero<Pila<T>> CrearPilaSimplementeEncadenada(Natural tamano);

	template <class T>
	Puntero<Pila<T>> CrearPilaArray(Natural tamano);

	template <class T>
	bool Iguales(const Puntero<Pila<T>>& pila1, const Puntero<Pila<T>>& pila2, const Comparador<T>& comp);

	// Operacion 4: Cadenas
	Array<Cadena> Split(const Cadena& origen, char delimiter);
	Cadena Reverso(const Cadena& origen);

	// Operación 5: Lista Ordenada
	template <class T>
	Puntero<Lista<T>> CrearListaOrdenadaEncadenada();

	template <class T>
	Puntero<Lista<T>> CrearListaOrdenadaConArray();

	template <class T>
	bool ListasSonIguales(const Puntero<Lista<T>>& lista1, const Puntero<Lista<T>>& lista2, const Comparador<T>& comp);

	// Operación 6: Tad Cola Prioridad
	template <class T, class P>
	Puntero<ColaPrioridad<T, P>> CrearColaPrioridad(Natural tamano);

	// Operación 7: Ejercicio con Cola Prioridad
	template <class T>
	Array<T> MayoresN(Array<Array<T>> datos, const Comparador<T>& comp, Natural n);


private:
};

#include "SistemaTemplates.cpp"

#endif
