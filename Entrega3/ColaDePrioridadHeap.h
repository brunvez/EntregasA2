#ifndef COLADEPRIORIDADHEAP_H
#define COLADEPRIORIDADHEAP_H
#include "Array.h"
#include "Puntero.h"
#include "Tupla.h"
template <class T, class P>
class ColaDePrioridad {
public:
	ColaDePrioridad(int size);
	ColaDePrioridad() { last = 1; heap = Array<T>(1); };
	~ColaDePrioridad() {};
	void Encolar(const T&, const P&);
	T Desencolar();
	T Top() const;
	bool IsEmpty() const;
private:
	int last;
	Array<Puntero<Tupla<T, P>>> heap;
	//Funciones
	int Padre(int i) { return i / 2; };
	int HijoIzq(int i) { return i * 2; };
	int HijoDer(int i) { return i * 2 + 1; };
	void Swap(int i, int j) {
		Puntero<Tupla<T, P>> aux = heap[i];
		heap[i] = heap[j];
		heap[j] = aux;
	};
	void Flotar(int i);
	void Hundir(int i);
};

#include "ColaDePrioridadHeap.cpp"
#endif // !COLADEPRIORIDADHEAP_H