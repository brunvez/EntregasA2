#include "Sistema.h"
#include "LinkedList.h"

Sistema::Sistema() {

}

template<class T>
bool ArrayContains(Array<T> arr, T e) {
	for (int i = 0; i < (int)arr.Largo; i++) {
		if (e == arr[i])
			return true;
	}
	return false;
}

bool PasePorTodas(Puntero<LinkedList<int>> ciudadesPasar, Array<int> ciudadesPasadas) {
	auto it = ciudadesPasar->GetIterator();
	while (it.HayElemento()) {
		if (!ArrayContains(ciudadesPasadas, it.ElementoActual()))
			return false;
		it.Avanzar();
	}
	return true;
}

template<class T>
Array<T> AddLast(Array<T> arr, T e) {
	Array<T> ret(arr.Largo + 1);
	int i;
	for (i = 0; i < (int)arr.Largo; i++) {
		ret[i] = arr[i];
	}
	ret[i] = e;
	return ret;
}

template<class T>
Array<T> RemoveLast(Array<T> arr) {
	Array<T> ret(arr.Largo - 1);
	int i;
	for (i = 0; i < (int)ret.Largo; i++) {
		ret[i] = arr[i];
	}
	return ret;
}


void ViajeroBT(Matriz<nat> &mapa, int ciudadActual, int ciudadLlegada, Puntero<LinkedList<int>> ciudadesPasar, Array<int> ciudadesPasadas,
			   nat costoActual, nat costoMax, Puntero<LinkedList<Array<int>>> mejores, nat mejorCosto) {
	if (ciudadActual == ciudadLlegada && costoActual <= costoMax && PasePorTodas(ciudadesPasar, ciudadesPasadas)) {
		if (costoActual < mejorCosto || (mejorCosto == costoActual && ciudadesPasadas.Largo < mejores->GetFirst().Largo)) {
			mejores->Clear();

			mejores->AddFirst(ciudadesPasadas);
			mejorCosto = costoActual;
		} else if (mejorCosto == costoActual) {
			mejores->AddFirst(ciudadesPasadas);
		}
	} else {
		Array<int> arr = AddLast(ciudadesPasadas, ciudadActual);
		for (int i = 0; i < (int)mapa.Largo; i++) {
			if (mapa[ciudadActual][i] != 0 && (i == ciudadLlegada || !ArrayContains(arr, i))) {
				ViajeroBT(mapa, i, ciudadLlegada, ciudadesPasar, arr, costoActual + mapa[ciudadActual][i], costoMax, mejores, mejorCosto);
			}
		}
	}
}

Iterador<Iterador<Puntero<ICiudad>>> Sistema::Viajero(Array<Puntero<ICiudad>> &ciudadesDelMapa, Matriz<nat> &mapa, Puntero<ICiudad> &ciudadPartida,
													  Iterador<Puntero<ICiudad>> &ciudadesPasar, nat costoMax) {
	Puntero<LinkedList<int>> ciudadesPasarL = new LinkedList<int>();
	while (ciudadesPasar.HayElemento()) {
		int numeroCiudad = ciudadesPasar.ElementoActual()->ObtenerNumero();
		ciudadesPasarL->AddFirst(numeroCiudad);
		ciudadesPasar.Avanzar();
	}
	Puntero<LinkedList<Array<int>>> mejores = new LinkedList<Array<int>>();
	int ciudadActual = ciudadPartida->ObtenerNumero();
	Array<int> ciudadesPasadas(1);
	ciudadesPasadas[0] = ciudadActual;
	for (int i = 0; i < (int)mapa.Largo; i++) {
		if (mapa[ciudadActual][i] != 0 && !ArrayContains(ciudadesPasadas, i)) {
			ViajeroBT(mapa, i, ciudadActual, ciudadesPasarL, ciudadesPasadas, mapa[ciudadActual][i], costoMax, mejores, INT16_MAX);
		}
	}
	// transformar array de ints a ciudades y de ahi a iteradores
	return NULL;
}

Array<nat> Sistema::Intercalar(Array<nat> &arr, nat i, nat m, nat d) {
	Array<nat> aux(d - i + 1);
	int itDer = i;
	int itIzq = m + 1;
	int itAux = 0;
	while (itDer <= (int)m && itIzq <= (int)d) {
		if (arr[itIzq] < arr[itDer]) {
			aux[itAux++] = arr[itIzq++];
		} else {
			aux[itAux++] = arr[itDer++];
		}
	}
	while (itDer <= (int)m) {
		aux[itAux++] = arr[itDer++];
	}
	while (itIzq <= (int)d) {
		aux[itAux++] = arr[itIzq++];
	}

	for (int j = i; j <= (int)d; j++) {
		arr[j] = aux[j - i];
	}
	return arr;  //Retorno por defecto
}

enum Direccion { arriba, abajo, izquierda, derecha, centro };

Direccion CalcularNuevaDireccion(Tupla<nat, nat> actual, Tupla<nat, nat> sig) {
	if (actual.Dato1 < sig.Dato1) {
		return arriba;
	} else if (actual.Dato1 > sig.Dato1) {
		return abajo;
	} else if (actual.Dato2 < sig.Dato2) {
		return izquierda;
	} else if (actual.Dato2 > sig.Dato2) {
		return derecha;
	} else {
		assert(false);
		return centro;
	}
}

void LaberintoBT(Tupla<nat, nat> actual, Tupla<nat, nat> &fin,
				 Matriz<nat> &laberinto, int &minCambios, int actualCambios, Puntero<LinkedList<Tupla<nat, nat>>> movimientos, Array<Tupla<nat, nat>> &mejor, Direccion dir) {
	if (minCambios >= actualCambios) {
		movimientos->AddLast(actual);
		laberinto[actual.Dato1][actual.Dato2] = 0;
		if (actual == fin) {
			if (actualCambios < minCambios) {
				mejor = movimientos->ToArray();
				minCambios = actualCambios;
			}
		} else {
			int dy[] = { 1, -1, 0, 0 };
			int dx[] = { 0, 0, 1, -1 };
			for (int i = 0; i < 4; i++) {
				Tupla<int, int> pos(actual.Dato1 + dy[i], actual.Dato2 + dx[i]);
				if (pos.Dato1 < (int)laberinto.Largo && pos.Dato1 >= 0 && (int)laberinto.Ancho > pos.Dato2 && pos.Dato2 >= 0 && laberinto[pos.Dato1][pos.Dato2] != 0) {
					Direccion nuevaDir = CalcularNuevaDireccion(actual, pos);
					int incrementoDir = nuevaDir != dir ? 1 : 0;
					LaberintoBT(pos, fin, laberinto, minCambios, actualCambios + incrementoDir, movimientos, mejor, nuevaDir);
				}
			}
		}
		movimientos->Remove(actual);
		laberinto[actual.Dato1][actual.Dato2] = 1;
	}
}

Iterador<Tupla<nat, nat>> Sistema::Laberinto(Tupla<nat, nat> &inicio, Tupla<nat, nat> &fin, Matriz<nat> &laberinto) {
	Array<Tupla<nat, nat>> mejor;
	Puntero<LinkedList<Tupla<nat, nat>>> movimientos = new LinkedList<Tupla<nat, nat>>();
	int minCambios = INT16_MAX;
	LaberintoBT(inicio, fin, laberinto, minCambios, 0, movimientos, mejor, centro);
	return mejor.ObtenerIterador();  //Retorno por defecto
}

void DegustacionBT(Array<Producto> &productos, int pos, int &maxPreferencia, int preferenciaActual, int maxDinero, int maxCalorias,
				   int maxAlcohol, Array<nat> &mejorConsumidos, Array<nat> actualConsumidos) {
	if (pos == (int)productos.Largo) {
		if (maxAlcohol >= 0 && maxCalorias >= 0 && maxDinero >= 0 && maxPreferencia < preferenciaActual) {
			maxPreferencia = preferenciaActual;
			Array<nat>::Copiar(actualConsumidos, mejorConsumidos);
		}
	} else {
		for (int i = 0; i <= (int)productos[pos].maxUnidades; i++) {
			actualConsumidos[pos] = i;
			DegustacionBT(productos, pos + 1, maxPreferencia, preferenciaActual + productos[pos].preferencia * i, maxDinero - productos[pos].precio *i,
						  maxCalorias - productos[pos].calorias * i, maxAlcohol - productos[pos].alcohol *i, mejorConsumidos, actualConsumidos);
		}
	}
}

Array<nat> Sistema::Degustacion(Array<Producto> productos, nat maxDinero, nat maxCalorias, nat maxAlcohol) {
	Array<nat> consumidosMejor(productos.Largo, 0);
	Array<nat> consumidos(productos.Largo, 0);
	int maxPref = 0;
	DegustacionBT(productos, 0, maxPref, 0, maxDinero, maxCalorias, maxAlcohol, consumidosMejor, consumidos);
	return consumidosMejor;
}

Tupla<TipoRetorno, Iterador<nat>> Sistema::Viajero2(Matriz<Tupla<nat, nat, nat>> relacionesCiudades, Iterador<nat> CiudadesPasar, Iterador<nat> CiudadesNoPasar) {
	//Implementar.

	return Tupla<TipoRetorno, Iterador<nat>>();
}

Tupla<TipoRetorno, Array<nat>> Sistema::ProteccionAnimales(Array<Accion> acciones, nat maxVeterinarios, nat maxVehiculos, nat maxDinero, nat maxVacunas, nat maxVoluntarios) {
	//Implementar.

	return Tupla<TipoRetorno, Array<nat>>();
}

nat ElegirPivot(Array<nat> items, nat ini, nat fin) {
	nat m = (fin + ini) / 2;
	nat max = ini;
	nat min = fin;
	if (items[m] > items[max]) {
		max = m;
	}
	if (items[fin] < items[max]) {
		max = fin;
	}
	if (items[ini] < items[min]) {
		min = ini;
	}
	if (ini != min && ini != max) {
		return ini;
	}
	if (fin != min && ini != max) {
		return fin;
	}
	return m;
}

void Swap(Array<nat> arr, int pos1, int pos2) {
	nat aux = arr[pos1];
	arr[pos1] = arr[pos2];
	arr[pos2] = aux;
}

void quicksort(Array<nat> arr, int left, int right) {
	int min = (left + right) / 2;

	int i = left;
	int j = right;
	int pivot = arr[min];

	while (left < j || i < right) {
		while ((int)arr[i] < pivot)
			i++;
		while ((int)arr[j] > pivot)
			j--;

		if (i <= j) {
			Swap(arr, i, j);
			i++;
			j--;
		} else {
			if (left < j)
				quicksort(arr, left, j);
			if (i < right)
				quicksort(arr, i, right);
			return;
		}
	}
}

Array<nat> Sistema::QuickSort(Array<nat> elementos) {
	quicksort(elementos, 0, elementos.Largo - 1);

	return elementos;
}

int CantidadPasadas(Tupla<int, int> inicio, int dx, int dy, Tupla<int, int> final, Matriz<int> mat) {
	int i = inicio.Dato1;
	int j = inicio.Dato2;
	int cont = 0;
	int incY = dy > 0 ? 1 : -1;
	int incX = dx > 0 ? 1 : -1;
	for (; i != final.Dato1; i += incY) {
		if (mat[i][j] == 1)
			cont++;
	}
	for (; j != final.Dato2; j += incX) {
		if (mat[i][j] == 1)
			cont++;
	}
	return cont;
}

void CaminoCaballoBT(Tupla<int, int> actual, Tupla<int, int> destino, Matriz<int> &tablero,
					 int pFaltan, LinkedList<Tupla<int, int>> listaActual, Puntero<LinkedList<Array<Tupla<int, int>>>> mejores) {

	if (listaActual.Size() < 10 && (mejores->IsEmpty() || listaActual.Size() <= (int)mejores->GetFirst().Largo)) {
		int casilla = tablero[actual.Dato1][actual.Dato2];
		listaActual.AddLast(actual);
		tablero[actual.Dato1][actual.Dato2] = -1;
		if (actual == destino && pFaltan - casilla <= 0) {
			if (mejores->IsEmpty() || listaActual.Size() == (int)mejores->GetFirst().Largo) {
				mejores->AddFirst(listaActual.ToArray());
			} else if (listaActual.Size() < (int)mejores->GetFirst().Largo) {
				mejores->Clear();
				mejores->AddFirst(listaActual.ToArray());
			}
		} else {
			int dx[] = { 1, -1, 1, -1, 2, 2, -2, -2 };
			int dy[] = { -2, -2, 2, 2, 1, -1, 1, -1 };
			int incrementoP = casilla == 1 ? 1 : 0;
			for (int i = 0; i < 8; i++) {
				Tupla<int, int> pos(actual.Dato1 + dy[i], actual.Dato2 + dx[i]);
				if (pos.Dato1 < (int)tablero.Largo && pos.Dato1 >= 0 && (int)tablero.Largo > pos.Dato2 && pos.Dato2 >= 0 && tablero[pos.Dato1][pos.Dato2] != -1) {
					CaminoCaballoBT(pos, destino, tablero, pFaltan - incrementoP, listaActual, mejores);
				}
			}
		}
		tablero[actual.Dato1][actual.Dato2] = casilla;
		listaActual.Remove(actual);
	}
}

Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>> Sistema::CaminoCaballo(Tupla<int, int>& salida, Tupla<int, int>& destino, nat cantAPasar,
																			   nat tamTablero, Iterador<Tupla<int, int>>& pasar, Iterador<Tupla<int, int>>& noPasar) {
	Matriz<int> mat(tamTablero);
	while (pasar.HayElemento()) {
		Tupla<nat, nat> pos = pasar.ElementoActual();
		mat[pos.Dato1][pos.Dato2] = 1;
		pasar.Avanzar();
	}

	while (noPasar.HayElemento()) {
		Tupla<nat, nat> pos = noPasar.ElementoActual();
		mat[pos.Dato1][pos.Dato2] = 0;
		noPasar.Avanzar();
	}
	LinkedList<Tupla<int, int>> listaActual = LinkedList<Tupla<int, int>>();
	Puntero <LinkedList<Array<Tupla<int, int>>>> mejores = new LinkedList<Array<Tupla<int, int>>>();
	CaminoCaballoBT(salida, destino, mat, cantAPasar, listaActual, mejores);
	Puntero<LinkedList<Iterador<Tupla<int, int>>>> iteradores = new LinkedList<Iterador<Tupla<int, int>>>();
	auto it = mejores->GetIterator();
	while (it.HayElemento()) {
		iteradores->AddFirst(it.ElementoActual().ObtenerIterador());
		it.Avanzar();
	}
	return Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>>(OK, iteradores->GetIterator());
}

Tupla<TipoRetorno, Array<nat>> Sistema::OptimizarGranja(Array<Tupla<nat, nat, nat>>& semillas, nat dinero, nat tierra, nat agua) {
	//Implementar.

	return Tupla<TipoRetorno, Array<nat>>();
}

Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>> Sistema::InscribirMaterias(Iterador<Tupla<Cadena, nat, nat>> matutino, Iterador<Tupla<Cadena, nat, nat>> nocturno, nat horasM, nat horasN) {
	//Implementar.

	return Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>>();
}


