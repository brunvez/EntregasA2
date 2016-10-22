#ifndef COLADEPRIORIDADHEAP_CPP
#define COLADEPRIORIDADHEAP_CPP
#include "ColaDePrioridadHeap.h"


template<class T, class P>
ColaDePrioridad<T, P>::ColaDePrioridad(int size) {
	heap = Array<Puntero<Tupla<T, P>>>(size);
	last = 0; //Primera posicion basura para simplificar padre e hijos
}

template<class T, class P>
void ColaDePrioridad<T, P>::Encolar(const T & e, const P & p) {
	if ((int)heap.Largo <= last + 1) {
		Array<Puntero<Tupla<T, P>>> arr(2 * heap.Largo);
		for (int i = 0; i < (int)heap.Largo; i++) {
			arr[i] = heap[i];
		}
		heap = arr;
	}
	heap[++last] = new Tupla<T, P>(e, p);
	Flotar(last);
}

template<class T, class P>
T ColaDePrioridad<T, P>::Desencolar() {
	assert(!IsEmpty());
	T elem = heap[1]->Dato1;
	Swap(1, last);
	heap[last--] = NULL;
	Hundir(1);
	return elem;
}

template<class T, class P>
T ColaDePrioridad<T, P>::Top() const {
	return heap[1]->Dato1;
}

template<class T, class P>
bool ColaDePrioridad<T, P>::IsEmpty() const {
	return last <= 0;
}

template<class T, class P>
void ColaDePrioridad<T, P>::Flotar(int i) {
	assert(i != 0);
	int p = Padre(i);
	if (i != 1 && heap[i]->Dato2 < heap[p]->Dato2) {
		Swap(i, p);
		Flotar(p);
	}
}

template<class T, class P>
void ColaDePrioridad<T, P>::Hundir(int i) {
	if (heap[i] != NULL) {
		int hDer = HijoDer(i);
		if (hDer <= last && heap[hDer] != NULL && heap[i]->Dato2 > heap[hDer]->Dato2) {
			Swap(i, hDer);
			Hundir(hDer);
		}
		int hIzq = HijoIzq(i);
		if (hIzq <= last && heap[hIzq] != NULL && heap[i]->Dato2 > heap[hIzq]->Dato2) {
			Swap(i, hIzq);
			Hundir(hIzq);
		}
	}
}


#endif // !COLADEPRIORIDADHEAP_CPP