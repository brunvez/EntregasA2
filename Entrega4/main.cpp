#include "CasoDePrueba.h"
#include "PruebaMemoria.h"
#include "ConductorPrueba.h"
#include "Sistema.h"

#include "GrafoMatriz.h"
#include "IntFuncionHash.h"
#include "Costo.h"
Puntero<Sistema> Inicializar(nat max) {
	return new Sistema(max);
}

Costo f(int i) { 
	return *new Costo(Tupla<int,int,int>(i,0,0)); };

void main() {
	Sistema s(13);
	Puntero<Grafo<int, int>> g = new GrafoMatriz<int, int>(5, new IntFuncionHash(), Comparador<int>::Default);
	int nums[5] = { 1, 2, 3, 4, 5 };
	g->AgregarVertice(nums[0]);
	g->AgregarVertice(nums[1]);
	g->AgregarVertice(nums[2]);
	g->AgregarVertice(nums[3]);
	g->AgregarVertice(nums[4]);
	g->AgregarArco(nums[0], nums[1], 1);
	g->AgregarArco(nums[1], nums[2], 2);
	g->AgregarArco(nums[1], nums[3], 3);
	g->AgregarArco(nums[3], nums[4], 4);
	g->AgregarArco(nums[1], nums[4], 3);
	g->AgregarArco(nums[3], nums[2], 1);
	auto f = [](int i)->Costo {
		return *new Costo(Tupla<int, int, int>(i, 0, 0));
	};
	auto it1 = s.ArbolCubrimientoMinimo(g, f);
	while (it1.HayElemento()) {
		auto e = it1.ElementoActual();
		cout << e.Dato1 << " " << e.Dato2 << endl;
		it1.Avanzar();
	}
	bool hC = s.HayCamino(g, nums[0], nums[4]);
	hC = s.HayCamino(g, nums[1], nums[3]);
	hC = s.HayCamino(g, nums[2], nums[3]);
	auto g2 = g->Clon();
	hC = s.HayCamino(g2, nums[0], nums[4]);
	hC = s.HayCamino(g2, nums[1], nums[3]);
	hC = s.HayCamino(g2, nums[2], nums[3]);
	g2->BorrarArco(nums[3], nums[4]);
	int con = s.EsConexo(g);
	con = s.EsConexo(g2);
	auto it = s.OrdenTopologico(g);
	while (it.HayElemento()) {
		cout << it.ElementoActual() << endl;
		it.Avanzar();
	}
	Puntero<ConductorPrueba> cp = new ConductorPrueba();
	Array<Puntero<Prueba>> pruebas = Array<Puntero<Prueba>>(3);
	pruebas[0] = new PruebaMemoria();
	pruebas[1] = new CasoDePrueba(Inicializar);
	pruebas[2] = pruebas[0];
	cp->CorrerPruebas(pruebas.ObtenerIterador());
	system("pause");
}
//template <class V, class A>
//Iterador<Tupla<V, V>> Sistema::ArbolCubrimientoMinimo(Puntero<Grafo<V, A>> g, int(*f)(A)) const {
//	int vertices = g->CantidadVertices();
//	Array<Tupla<V, int, bool, V>> arr(vertices);
//	auto it = g->Vertices();
//	int i = 0;
//	Puntero<ColaDePrioridad<V, int>> cola = new ColaDePrioridad<V, int>(vertices);
//	Puntero<LinkedList<Tupla<V, V>>> l = new LinkedList < Tupla<V, V>>();
//	while (it.HayElemento()) {
//		V v = it.ElementoActual();
//		arr[i].Dato1 = v;
//		arr[i].Dato2 = INT_MAX;
//		arr[i].Dato3 = false;
//		i++;
//		it.Avanzar();
//	}
//	arr[0].Dato2 = 0;
//	arr[0].Dato3 = true;
//	cola->Encolar(arr[0].Dato1, 0);
//	bool first = true;
//	while (!cola->IsEmpty()) {
//		V v = cola->Desencolar();
//		int index = IndexOf(arr, v);
//		if (!first) {
//			l->AddLast(Tupla<V, V>(arr[index].Dato4, v));
//		}
//		first = false;
//		arr[index].Dato3 = true;
//		it = g->Adyacentes(v);
//		while (it.HayElemento()) {
//			V elem = it.ElementoActual();
//			if (!EsConocido(arr, elem)) {
//				int index2 = IndexOf(arr, elem);
//				int cost = f(g->ObtenerArco(v, elem));
//				if (cost < arr[index2].Dato2) {
//					cola->Encolar(elem, cost);
//					arr[index2].Dato2 = cost;
//					arr[index2].Dato4 = v;
//				}
//			}
//			it.Avanzar();
//		}
//	}
//	return l->GetIterator();
//}
