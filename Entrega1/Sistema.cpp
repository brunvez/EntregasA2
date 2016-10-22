#ifndef SISTEMA_CPP
#define SISTEMA_CPP

#include "Sistema.h"

Sistema::Sistema() {
}
Sistema::~Sistema() {
}

// Ejercicio 1: ordenamiento
void Sistema::OrdenarEnteros(Array<int>& elementos, const Comparador<int>& comp) {
	Array<int> arr = Array<int>(3000);
	for (int i = 0; i < 3000; i++) {
		arr[i] = 0;
	}
	for (int i = 0; i < (int)elementos.ObtenerLargo(); i++) {
		arr[elementos[i] / 2]++;
	}
	int j = 0;
	for (int i = 0; i < 3000; i++) {
		if (arr[i] != 0) { // redundante
			for (int k = 0; k < arr[i]; k++) {
				elementos[j] = i * 2;
				j++;
			}
		}
	}
}

// Operación 2: Búsqueda
bool Sistema::ExisteSuma(const Array<int>& elementos, int suma) {
	Array<int> arr = Array<int>(elementos.ObtenerLargo());
	Array<int>::Copiar(elementos, arr);  //?????? asumo n
	Ordenar(arr, Comparador<int>()); // n * log n
	for (int i = 0; i < (int)arr.ObtenerLargo(); i++) { // n
		int index = Busqueda(arr, suma - arr[i], Comparador<int>());
		if (index != -1 && index != i) { // log n
			return true;
		}
	} // n * log n
	return false;

}

int CountDelimiters(const Cadena& str, char delimiter) {
	int cant = 0;
	bool count = true;
	int i = 0;
	while (str[i] == delimiter) {
		i++;
	}
	for (i; i < (int)str.ObtenerLargo(); i++) {
		char c = str[i];
		if (count && c == delimiter) {
			cant++;
			count = false;
		} else if (c != delimiter) {
			count = true;
		}
	}
	if (str[str.ObtenerLargo() - 1] != delimiter)
		cant++;
	return cant;
}

// Operacion 4: Cadenas
Array<Cadena> Sistema::Split(const Cadena& origen, char delimiter) {
	int cant = CountDelimiters(origen, delimiter);
	Array<Cadena> arr = Array<Cadena>(cant);
	int j = 0;
	int i = 0;
	bool add = true;
	string str = "";

	while (origen[i] == delimiter) {
		i++;
	}
	for (i; i < (int)origen.ObtenerLargo(); i++) {
		if (add && origen[i] == delimiter) {
			arr[j] = Cadena(str.c_str());
			add = false;
			str = "";
			j++;
		} else if (origen[i] != delimiter) {
			str += origen[i];
			add = true;
		}
	}
	if (j < cant)
		arr[j] = Cadena(str.c_str());
	return arr;
}

Cadena Sistema::Reverso(const Cadena& origen) {
	Array<Cadena> arr = Split(origen, ' ');
	int length = (int)arr.ObtenerLargo();
	PilaArray<Cadena> p = PilaArray<Cadena>(length);
	for (int i = 0; i < length; i++) {
		p.Push(arr[i]);
	}
	Cadena str = "";
	for (int i = 0; i < length; i++) {
		str += p.Top() + (i== length -1 ? "":" ");
		p.Pop();
	}
	return str;
}



#endif