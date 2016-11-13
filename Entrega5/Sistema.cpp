#include "Sistema.h"
#include <stdio.h>
#include <string>
#include "LinkedList.h"

Sistema::Sistema() {

}

void swap(int i1, int j1, int i2, int j2, Matriz<nat> matriz) {
	nat aux = matriz[i1][j1];
	matriz[i1][j1] = matriz[i2][j2];
	matriz[i2][j2] = aux;
}

void TransponerMatrizRec(Matriz<nat> matriz, int desdeX, int hastaX, int desdeY, int hastaY) {
	if (hastaX - desdeX >= 2 && hastaY - desdeY >= 2) {
		// caudrantes
		// 1 | 2
		// 4 | 3
		TransponerMatrizRec(matriz, desdeX, (hastaX + desdeX) / 2, desdeY, (hastaY + desdeY) / 2); // cuadrante 1
		TransponerMatrizRec(matriz, (hastaX + desdeX) / 2, hastaX, (hastaY + desdeY) / 2, hastaY); // cuadrante 3
		TransponerMatrizRec(matriz, (hastaX + desdeX) / 2, hastaX, desdeY, (hastaY + desdeY) / 2); // cuadrante 2
		TransponerMatrizRec(matriz, desdeX, (hastaX + desdeX) / 2, (hastaY + desdeY) / 2, hastaY); // cuadrante 4
		int largo = (hastaX - desdeX) / 2;
		int inicialX = (desdeX + hastaX) / 2;
		int inicialY = (desdeY + hastaY) / 2;
		for (int i = 0; i < largo; i++) {
			for (int j = 0; j < largo; j++) {
				swap(inicialX + i, desdeY + j, desdeX + i, inicialY + j, matriz);
			}
		}
	}
}

void Sistema::TransponerMatriz(Matriz<nat> matriz) {
	TransponerMatrizRec(matriz, 0, matriz.Largo, 0, matriz.Ancho);
};

int max(int a, int b) { return a < b ? b : a; }

Array<Puntero<ITira>> IntercalarSiluetas(Array<Puntero<ITira>> s1, Array<Puntero<ITira>> s2) {
	int h1 = 0;
	int h2 = 0;
	auto it1 = s1.ObtenerIterador();
	auto it2 = s2.ObtenerIterador();
	Puntero<LinkedList<Puntero<ITira>>> l = new LinkedList<Puntero<ITira>>();
	while (it1.HayElemento() && it2.HayElemento()) {
		Puntero<ITira> e1 = it1.ElementoActual();
		Puntero<ITira> e2 = it2.ElementoActual();
		if ((int)e1->ObtenerX() < e2->ObtenerX()) {
			if ((int)e1->ObtenerAltura() > h2) {
				h1 = e1->ObtenerAltura();
				l->AddLast(e1);
			} else if ((int)e1->ObtenerAltura() < h1 && h1 > h2) {
				Puntero<ITira> tira = new Tira(e1->ObtenerX(), h2);
				h1 = h2;
				l->AddLast(tira);
			} else {
				h1 = e1->ObtenerAltura();
			}
			it1.Avanzar();
		} else {
			if ((int)e2->ObtenerAltura() > h1) {
				h2 = e2->ObtenerAltura();
				l->AddLast(e2);
			} else if ((int)e2->ObtenerAltura() < h2 && h2 > h1) {
				Puntero<ITira> tira = new Tira(e2->ObtenerX(), h1);
				h2 = h1;
				l->AddLast(tira);
			} else {
				h2 = e2->ObtenerAltura();
			}
			it2.Avanzar();
		}
	}
	while (it1.HayElemento()) {
		Puntero<ITira> e = it1.ElementoActual();
		l->AddLast(e);
		it1.Avanzar();
	}
	while (it2.HayElemento()) {
		Puntero<ITira> e = it2.ElementoActual();
		l->AddLast(e);
		it2.Avanzar();
	}
	Array<Puntero<ITira>> arr(l->Size());
	auto it = l->GetIterator();
	int i = 0;
	while (it.HayElemento()) {
		arr[i++] = it.ElementoActual();
		it.Avanzar();
	}
	return arr;
}

Array<Puntero<ITira>> CalcularSiluetaRec(Array<Puntero<IEdificio>> ciudad, int inicio, int fin) {
	if (inicio == fin) {
		Array<Puntero<ITira>> silueta(2);
		silueta[0] = new Tira(ciudad[inicio]->ObtenerXInicial(), ciudad[inicio]->ObtenerAltura());
		silueta[1] = new Tira(ciudad[inicio]->ObtenerXFinal(), 0);
		return silueta;
	} else {
		int mid = (inicio + fin) / 2;
		Array<Puntero<ITira>> s1 = CalcularSiluetaRec(ciudad, inicio, mid);
		Array<Puntero<ITira>> s2 = CalcularSiluetaRec(ciudad, mid + 1, fin);
		return IntercalarSiluetas(s1, s2);
	}
};

Array<Puntero<ITira>> Sistema::CalcularSiluetaDeLaCiudad(Array<Puntero<IEdificio>> ciudad) {
	return CalcularSiluetaRec(ciudad, 0, ciudad.Largo - 1);
};


nat Sistema::CalcularCoeficienteBinomial(nat n, nat k) {
	Array<int> anterior(n + 1, 0);
	anterior[0] = 1;
	Array<int> actual(n + 1, 0);
	actual[0] = 1;
	for (int i = 1; i <= (int)n; i++) {
		for (int j = 1; j <= i; j++) {
			actual[j] = anterior[j - 1] + anterior[j];
		}
		Array<int> aux = anterior;
		anterior = actual;
		actual = aux;
	}
	return anterior[k];
};


