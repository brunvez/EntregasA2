#include "CasoDePrueba.h"
#include "PruebaMemoria.h"
#include "ConductorPrueba.h"
#include "Sistema.h"

#include "LinkedList.h"

Puntero<Sistema> Inicializar() {
	return new Sistema();
}

void main() {
	bool consola = false;
	/*Puntero<LinkedList<int>> l = new LinkedList<int>();
	int i1 = 1;
	int i2 = 2;
	int i3 = 3;
	int i4 = 4;
	int i5 = 5;
	int i6 = 6;
	int i7 = 7;
	l->AddFirst(i1);
	l->AddFirst(i2);
	l->AddFirst(i3);
	l->AddFirst(i4);
	l->AddFirst(i5);
	l->AddFirst(i6);
	l->AddFirst(i7);
	l->AddLast(i7);
	Array<int> arr = l->ToArray();
	auto it = l->GetIterator();
	while (it.HayElemento()) {
		cout << it.ElementoActual() << endl;
		it.Avanzar();
	}*/
	if (!consola) {
		Puntero<ConductorPrueba> cp = new ConductorPrueba();
		Array<Puntero<Prueba>> pruebas = Array<Puntero<Prueba>>(3);
		pruebas[0] = new PruebaMemoria();
		pruebas[1] = new CasoDePrueba(Inicializar);
		pruebas[2] = pruebas[0];
		cp->CorrerPruebas(pruebas.ObtenerIterador());
	} else {

		cout << endl << "--- Prueba por consola del Juego del 8 ---" << endl << endl;
		cout << "Ingrese la dimension del tablero: ";
		int n;
		cin >> n;
		cout << endl << "Ingrese el tablero. Una fila por linea, separando los numeros con espacios. Use 0 para la posicion libre." << endl;

		Matriz<int> bloques = Matriz<int>(n);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> bloques[i][j];

		Tablero* inicial = new Tablero(bloques);

		Puntero<Sistema> s = new Sistema();

		s->EstablecerTableroInicial(*inicial);

		cout << endl;

		if (!s->TieneSolucion()) {
			cout << "Sin solucion." << endl;
		} else {
			Iterador<Tablero> pasos = s->Solucionar();

			pasos.Reiniciar();

			while (pasos.HayElemento()) {
				cout << pasos.ElementoActual().Imprimir() << endl;
				pasos.Avanzar();
			}
			Cadena c = "Cantidad de movimientos requeridos = ";
			cout << endl << c << s->Movimientos() << endl;
		}
	}
	system("pause");
}
