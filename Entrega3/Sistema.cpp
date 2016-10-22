#ifndef SOLUCION_CPP
#define SOLUCION_CPP

#include "Sistema.h"
#include "LinkedList.h"

Sistema::Sistema() {
}

Matriz<int> SolucionNxN(int n) {
	Matriz<int> mat(n);
	int cont = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mat[i][j] = ++cont;
		}
	}
	mat[n - 1][n - 1] = 0;
	return mat;
}

void Sistema::EstablecerTableroInicial(Tablero inicial) {
	Tablero solucion(SolucionNxN(inicial.ObtenerTablero().Largo));
	int inversions = 0;
	int index = 0;
	int n = (int)inicial.ObtenerTablero().Largo;
	int n2 = n*n;
	bool blankOnOdd = false;
	Array<int> arr(n2);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[index++] = inicial.ObtenerTablero()[i][j];
			if (inicial.ObtenerTablero()[i][j] == 0)
				blankOnOdd = (n - i) % 2 != 0;
		}
	}
	for (int i = 0; i < n2; i++) {
		if (arr[i] != 0)
			for (int j = i; j < n2; j++) {
				if (arr[i] > arr[j] && arr[j] != 0)
					inversions++;
			}
	}
	if (((n % 2 != 0) && (inversions % 2 == 0)) || ((n % 2 == 0) && ((blankOnOdd) == (inversions % 2 == 0)))) {
		Puntero<ColaDePrioridad<Puntero<Estado>, int>> c1 = new ColaDePrioridad<Puntero<Estado>, int>(1);
		c1->Encolar(new Estado(inicial, 0), inicial.PrioridadB());
		while (c1->Top()->actual != solucion) {
			Puntero<Estado> aux1 = c1->Desencolar();
			Puntero<Estado> e1 = new Estado(aux1->actual, aux1->moves, aux1->ant);
			auto it = e1->actual.Vecinos();
			while (it.HayElemento()) {
				Tablero tab = it.ElementoActual();
				if (e1->ant == NULL || e1->ant->actual != tab)
					c1->Encolar(new Estado(tab, e1->moves + 1, e1), tab.PrioridadB() + e1->moves);
				it.Avanzar();
			}
		}
		this->solucion = c1->Desencolar();
		this->tieneSol = true;
	} else {
		this->tieneSol = false;
	}
}

bool Sistema::TieneSolucion() {
	return tieneSol;
}

int Sistema::Movimientos() {
	return solucion->moves;
}

Iterador<Tablero> Sistema::Solucionar() {
	Puntero<Estado> aux = solucion;
	Puntero<LinkedList<Tablero>> l = new LinkedList<Tablero>();
	while (aux != nullptr) {
		l->AddFirst(aux->actual);
		aux = aux->ant;
	}
	return l->GetIterator();
}


#endif