#ifndef SISTEMATEMPLATES_CPP
#define SISTEMATEMPLATES_CPP

#include "Sistema.h"
#include "PilaEncadenada.h"
#include "PilaArray.h"
#include "ArrayListOrdenado.h"
#include "LinkedListOrdenado.h"
#include "ColaPrioridadImp.h"

// Ejercicio 1: ordenamiento
template <class T>
void Sistema::Ordenar(Array<T>& elementos, const Comparador<T>& comp) {
	mergeSort(elementos, 0, elementos.ObtenerLargo() - 1, comp);
}

// Operación 2: Búsqueda
template <class T>
int Sistema::Busqueda(const Array<T>& elementos, const T& elem, const Comparador<T>& comp) {
	return binarySearch(elementos, elem, comp, 0, (int)elementos.ObtenerLargo() - 1);
}

// Operación 3: TAD Pila
template <class T>
Puntero<Pila<T>> Sistema::CrearPilaSimplementeEncadenada(Natural tamano) {
	Pila<T> * p = new PilaEncadenada<T>((int)tamano);
	return Puntero<Pila<T>>(p);
	return Puntero<Pila<T>>();
}

template <class T>
Puntero<Pila<T>> Sistema::CrearPilaArray(Natural tamano) {
	Pila<T> * p = new PilaArray<T>((int)tamano);
	return Puntero<Pila<T>>(p);
	return Puntero<Pila<T>>();
}

template <class T>
bool Sistema::Iguales(const Puntero<Pila<T>>& pila1, const Puntero<Pila<T>>& pila2, const Comparador<T>& comp) {
	Puntero<Pila<T>> p1 = pila1->Clon();
	Puntero<Pila<T>> p2 = pila2->Clon();
	while (!p1->EstaVacia() && !p2->EstaVacia()) {
		if (p1->Top() != p2->Top()) {
			return false;
		}
		p1->Pop();
		p2->Pop();
	}
	return p1->EstaVacia() && p2->EstaVacia();
	return false;
}

// Operación 5: Lista Ordenada
template<class T>
Puntero<Lista<T>> Sistema::CrearListaOrdenadaEncadenada() {
	Lista<T> * l = new LinkedListOrdenado<T>();
	return Puntero<Lista<T>>(l);
}

template <class T>
Puntero<Lista<T>> Sistema::CrearListaOrdenadaConArray() {
	Lista<T> * l = new ArrayListOrdenado<T>();
	return Puntero<Lista<T>>(l);
}

template <class T>
bool Sistema::ListasSonIguales(const Puntero<Lista<T>>& lista1, const Puntero<Lista<T>>& lista2, const Comparador<T>& comp) {
	if (lista1->Largo() != lista2->Largo()) return false;
	for (int i = 0; i < (int)lista1->Largo(); i++) {
		if (comp.SonDistintos(lista1->Obtener(i), lista2->Obtener(i)))
			return false;
	}
	return true;
}

// Operación 6: Tad Cola de Prioridad
template<class T, class P>
Puntero<ColaPrioridad<T, P>> Sistema::CrearColaPrioridad(Natural tamano) {
	ColaPrioridad<T, P> *c = new ColaPrioridadImp<T, P>(tamano);
	return Puntero<ColaPrioridad<T, P>>(c);
}


// Operación 7: Ejercicio con Cola de Prioridad
template <class T>
Array<T> Sistema::MayoresN(Array<Array<T>> datos, const Comparador<T>& comp, Natural n) {
	Puntero <ColaPrioridad<T, T>> cp = new ColaPrioridadImp<T, T>(n);
	bool primero = true;
	int encolados = 0;
	T t;
	for (int i = 0; i < (int)datos.ObtenerLargo(); i++) {
		for (int j = 0; j < (int)datos[i].ObtenerLargo(); j++) {
			T d = datos[i][j];
			if (primero) {
				t = d;
				cp->Encolar(d, d);
				encolados++;
				primero = false;
			} else if (encolados < (int)n) {
				t = comp.EsMenor(d, t) ? d : t;
				cp->Encolar(d, d);
				encolados++;
			} else if(comp.EsMayor(d, t)) {
				t = d;
				cp->Encolar(d, d);
				encolados++;
			}
		}
	}
	Array<T> arr = Array<T>(n);
	for (int i = 0; i < (int)n; i++) {
		arr[i] = cp->Desencolar();
	}
	return arr;
}

//Auxiliares
template <class T>
void Sistema::merge(Array<T>& arr, int l, int m, int r, const Comparador<T>& comp) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* temp arrays */
	Array<T> L = Array<T>(n1);
	Array<T> R = Array<T>(n2);

	/* copy data */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* return data to original but ordered*/
	i = 0; // first subarray
	j = 0; // second subarray
	k = l; // original subarray
	while (i < n1 && j < n2) {
		if (comp.EsMenor(L[i], R[j])) {
			arr[k] = L[i];
			i++;
		} else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}


template <class T>
void Sistema::mergeSort(Array<T>& arr, int l, int r, const Comparador<T>& comp) {
	if (l < r) {
		int m = l + (r - l) / 2;

		mergeSort(arr, l, m, comp);
		mergeSort(arr, m + 1, r, comp);

		merge(arr, l, m, r, comp);
	}
}

template <class T>
int Sistema::binarySearch(const Array<T>& arr, const T& value, const Comparador<T>& c, int left, int right) {
	while (left <= right) {
		int middle = (left + right) / 2;
		if (c.SonIguales(arr[middle], value))
			return middle;
		else if (c.EsMayor(arr[middle], value))
			right = middle - 1;
		else
			left = middle + 1;
	}
	return -1;
}

#endif