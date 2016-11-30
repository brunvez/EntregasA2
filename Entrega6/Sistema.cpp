#include "Sistema.h"
#include "LinkedList.h"

Sistema::Sistema() {

}

Iterador<Iterador<Puntero<ICiudad>>> Sistema::Viajero(Array<Puntero<ICiudad>> &ciudadesDelMapa, Matriz<nat> &mapa, Puntero<ICiudad> &ciudadPartida, Iterador<Puntero<ICiudad>> &ciudadesPasar, nat costoMax) {
	/*
   Codigo de implementacion de la solucion
   */
	return NULL; //Retorno por defecto
}

Array<nat> Sistema::Intercalar(Array<nat> &arreglo, nat i, nat m, nat d) {
	/*
   Codigo de implementacion de la solucion
   */
	return Array<nat>(arreglo.Largo);  //Retorno por defecto
}

enum direccion { arriba, abajo, izquierda, derecha, centro };

Iterador<Tupla<nat, nat>> LaberintoBT(Tupla<nat, nat> actual, Tupla<nat, nat> &fin,
	Matriz<nat> &laberinto, int& minCambios, int& actualCambios, Puntero<LinkedList<Tupla<nat, nat>>> movimientos) {
	if (actual == fin) {
		if (actualCambios < minCambios) {
			minCambios = actualCambios;
			movimientos->AddLast(actual);
			return movimientos->GetIterator();
		}
	}
	int dx[] = { -1, 0, 1,  0 };
	int dy[] = { 0, 1, 0, -1 };

	return NULL;
}

Iterador<Tupla<nat, nat>> Sistema::Laberinto(Tupla<nat, nat> &inicio, Tupla<nat, nat> &fin, Matriz<nat> &laberinto) {
	/*
	Codigo de implementacion de la solucion
	*/
	return NULL;  //Retorno por defecto
}

Array<nat> Sistema::Degustacion(Array<Producto> productos, nat maxDinero, nat maxCalorias, nat maxAlcohol) {
	/*
	Codigo de implementacion de la solucion
	*/
	return Array<nat>(productos.Largo);  //Retorno por defecto
}

Tupla<TipoRetorno, Iterador<nat>> Sistema::Viajero2(Matriz<Tupla<nat, nat, nat>> relacionesCiudades, Iterador<nat> CiudadesPasar, Iterador<nat> CiudadesNoPasar) {
	//Implementar.

	return Tupla<TipoRetorno, Iterador<nat>>();
}

Tupla<TipoRetorno, Array<nat>> Sistema::ProteccionAnimales(Array<Accion> acciones, nat maxVeterinarios, nat maxVehiculos, nat maxDinero, nat maxVacunas, nat maxVoluntarios) {
	//Implementar.

	return Tupla<TipoRetorno, Array<nat>>();
}

Array<nat> Sistema::QuickSort(Array<nat> elementos) {
	//Implementar.

	return Array<nat>();
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
				int a = pos.Dato1;
				int b = pos.Dato2;
				if (pos.Dato1 < (int)tablero.Largo && pos.Dato1 >= 0 && (int)tablero.Largo > pos.Dato2 && pos.Dato2 >= 0 && tablero[pos.Dato1][pos.Dato2] != -1) {
					//int incrementoP = CantidadPasadas(actual, dx[i], dy[i], pos, tablero);
					CaminoCaballoBT(pos, destino, tablero, pFaltan - incrementoP, listaActual, mejores);
				}
			}
		}
		tablero[actual.Dato1][actual.Dato2] = casilla;
		listaActual.Remove(actual);
	}
}

Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>> Sistema::CaminoCaballo(Tupla<int, int>& salida, Tupla<int, int>& destino, nat cantAPasar,
	nat tamTablero, Iterador<Tupla<int, int>>& pasar,
	Iterador<Tupla<int, int>>& noPasar) {
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


