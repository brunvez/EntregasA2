#include "CasoDePrueba.h"

CasoDePrueba::CasoDePrueba(Puntero<Sistema>(*inicializar)()) {
	this->inicializar = inicializar;
}

Puntero<Sistema> CasoDePrueba::InicializarSistema() {
	Puntero<Sistema> interfaz = inicializar();
	ignorarOK = false;
	return interfaz;
}

Cadena CasoDePrueba::GetNombre()const {
	return "Casos de Prueba";
}

void CasoDePrueba::CorrerPruebaConcreta() {

	PruebaOperacion1();
	PruebaOperacion2();
	PruebaOperacion3();
	PruebaOperacion4();
	PruebaOperacion5();
	PruebaOperacion6();
	PruebaOperacion7();
	PruebasPropias();
}

void CasoDePrueba::Verificar(TipoRetorno obtenido, TipoRetorno esperado, Cadena comentario) {
	if (!ignorarOK || obtenido != esperado)
		Prueba::Verificar(obtenido, esperado, comentario);
}

template <class T>
void CasoDePrueba::Verificar(const T& obtenido, const T& esperado, Cadena comentario) {
	Verificar(SonIguales(obtenido, esperado) ? OK : ERROR, OK, comentario.DarFormato(ObtenerTexto(obtenido), ObtenerTexto(esperado)));
}

template <class T>
void CasoDePrueba::VerificarConjuntos(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra) {
	bool verificarCantidad = true;
	nat totalObtenidos = 0;
	T aux;
	obtenidos.Reiniciar();
	esperados.Reiniciar();
	foreach(T obtenido, obtenidos) {
		totalObtenidos++;
		if (Pertenece(obtenido, esperados, aux))
			Verificar(OK, OK, comentarioEncontrado.DarFormato(ObtenerTexto(obtenido), ObtenerTexto(obtenido)));
		else {
			Verificar(ERROR, OK, comentarioSobra.DarFormato(ObtenerTexto(obtenido)));
			verificarCantidad = false;
		}
	}
	nat totalEsperados = 0;
	obtenidos.Reiniciar();
	esperados.Reiniciar();
	foreach(T esperado, esperados) {
		totalEsperados++;
		if (!Pertenece(esperado, obtenidos, aux)) {
			Verificar(ERROR, OK, comentarioFalta.DarFormato(ObtenerTexto(esperado)));
			verificarCantidad = false;
		}
	}
	if (verificarCantidad && totalObtenidos != totalEsperados)
		Verificar(ERROR, OK, "Se verifica la cantidad de elementos de los conjuntos");
}

template <class T>
void CasoDePrueba::VerificarSecuencias(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra) {
	esperados.Reiniciar();

	foreach(T obtenido, obtenidos) {
		if (esperados.HayElemento()) {
			T esperado = *esperados;
			++esperados;
			Verificar(obtenido, esperado, comentarioEncontrado);
		} else
			Verificar(ERROR, OK, comentarioSobra.DarFormato(ObtenerTexto(obtenido)));
	}

	while (esperados.HayElemento()) {
		T esperado = *esperados;
		++esperados;
		Verificar(ERROR, OK, comentarioFalta.DarFormato(ObtenerTexto(esperado)));
	}
}
bool CasoDePrueba::SonIguales(const Cadena& obtenidos, const Cadena& esperados) const {
	return obtenidos == esperados;
}
template <class T>
bool CasoDePrueba::SonIguales(Iterador<T> obtenidos, Iterador<T> esperados) const {
	obtenidos.Reiniciar();
	esperados.Reiniciar();
	while (obtenidos.HayElemento() && esperados.HayElemento()) {
		if (!SonIguales(*obtenidos, *esperados))
			return false;
		++obtenidos;
		++esperados;
	}

	return esperados.HayElemento() == obtenidos.HayElemento();
}

template <class T>
Cadena CasoDePrueba::ObtenerTexto(Iterador<T> it) const {
	Cadena sepVacio = "";
	Cadena sepGuion = "-";
	Cadena sep = sepVacio;
	Cadena retorno = sepVacio;
	foreach(auto t, it) {
		retorno += sep + ObtenerTexto(t);
		sep = sepGuion;
	}
	return retorno;
}

Cadena CasoDePrueba::ObtenerTexto(const Tupla<nat, nat>& t) const {
	Cadena ret = " {0} - {1} ";
	return ret.DarFormato(ObtenerTexto(t.Dato1), ObtenerTexto(t.Dato2));
}
Cadena CasoDePrueba::ObtenerTexto(Cadena n) const {
	return n;
}
Cadena CasoDePrueba::ObtenerTexto(nat n) const {
	switch (n) {
	case 0:
		return "0";
	case 1:
		return "1";
	case 2:
		return "2";
	case 3:
		return "3";
	case 4:
		return "4";
	case 5:
		return "5";
	case 6:
		return "6";
	case 7:
		return "7";
	case 8:
		return "8";
	case 9:
		return "9";
	default:
		Cadena ret = "";
		while (n != 0) {
			ret = ObtenerTexto(n % 10) + ret;
			n /= 10;
		}
		return ret;
	}
}

bool CasoDePrueba::SonIguales(const Tupla<nat, nat>& obtenido, const Tupla<nat, nat>& esperado) const {
	return (obtenido.Dato1 == esperado.Dato1 && obtenido.Dato2 == esperado.Dato2) ||
		(obtenido.Dato2 == esperado.Dato1 && obtenido.Dato1 == esperado.Dato2);
}

bool CasoDePrueba::SonIguales(const bool obtenido, const bool esperado) const {
	return obtenido == esperado;
}

bool CasoDePrueba::SonIguales(const int obtenido, const int esperado) const {
	return obtenido == esperado;
}

template <class T>
bool CasoDePrueba::Pertenece(const T& dato, Iterador<T> iterador, T& encontrado) const {
	iterador.Reiniciar();
	foreach(T dato2, iterador) {
		if (SonIguales(dato, dato2)) {
			encontrado = dato2;
			return true;
		}
	}
	return false;
}

//Operacion 1:
void CasoDePrueba::PruebaOperacion1() {
	IniciarSeccion("Operacion 1a");
	Puntero<Sistema> interfaz = InicializarSistema();
	Cadena mensaje = "";

	Array<Cadena> esperado(3);
	esperado[0] = "Felipe";
	esperado[1] = "Martin";
	esperado[2] = "Pedro";

	Array<Cadena> cadenas(3);
	cadenas[0] = "Martin";
	cadenas[1] = "Felipe";
	cadenas[2] = "Pedro";

	interfaz->Ordenar<Cadena>(cadenas, Comparador<Cadena>::Default);

	VerificarSecuencias(cadenas.ObtenerIterador(), esperado.ObtenerIterador(), "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");

	
	CerrarSeccion();

	IniciarSeccion("Operacion 1b");

	Array<int> esperado2(4);
	esperado2[0] = 850;
	esperado2[1] = 850;
	esperado2[2] = 1500;
	esperado2[3] = 2000;

	Array<int> enteros(4);
	enteros[0] = 850;
	enteros[1] = 1500;
	enteros[2] = 850;
	enteros[3] = 2000;

	interfaz->OrdenarEnteros(enteros, Comparador<int>::Default);

	VerificarSecuencias(enteros.ObtenerIterador(), esperado2.ObtenerIterador(), "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");

	
	CerrarSeccion();
}
//Operación 2:
void CasoDePrueba::PruebaOperacion2() {
	IniciarSeccion("Operacion 2a");
	Puntero<Sistema> interfaz = InicializarSistema();

	Array<Cadena> elementos(4);
	elementos[0] = "Felipe";
	elementos[1] = "Martin";
	elementos[2] = "Pedro";
	elementos[3] = "Zak";

	int obtenido = interfaz->Busqueda<Cadena>(elementos, "Pedro", Comparador<Cadena>::Default);
	int obtenido2 = interfaz->Busqueda<Cadena>(elementos, "Mauricio", Comparador<Cadena>::Default);


	Verificar(obtenido, 2, "Se verifica operacion 2a");
	Verificar(obtenido2, -1, "Se verifica operacion 2a");
	CerrarSeccion();

	IniciarSeccion("Operacion 2b");

	Array<int> elementos2(4);
	elementos2[0] = 4;
	elementos2[1] = 33;
	elementos2[2] = 15;
	elementos2[3] = 10;

	Verificar(interfaz->ExisteSuma(elementos2, 25), true, "Se verifica operacion 2b");
	Verificar(interfaz->ExisteSuma(elementos2, 26), false, "Se verifica operacion 2b");
	Verificar(interfaz->ExisteSuma(elementos2, 2), false, "Se verifica operacion 2b");
	Verificar(interfaz->ExisteSuma(elementos2, 37), true, "Se verifica operacion 2b");
	CerrarSeccion();
}
//Operación 3:
void CasoDePrueba::PruebaOperacion3() {
	IniciarSeccion("Operacion 3");
	Puntero<Sistema> interfaz = InicializarSistema();
	Cadena sonIguales = "Las pilas son iguales";
	Cadena sonDistintas = "Las pilas son distintas";

	Puntero<Pila<Cadena>> pila1 = interfaz->CrearPilaSimplementeEncadenada<Cadena>(100);
	Puntero<Pila<Cadena>> pila2 = interfaz->CrearPilaArray<Cadena>(100);

	if (pila1 == nullptr) {
		Verificar(false, true, "La pila retornada por CrearPilaSimplementeEncadenada es nula");
	}
	if (pila2 == nullptr) {
		Verificar(false, true, "La pila retornada por CrearPilaArray es nula");
	}
	if (pila1 != nullptr && pila2 != nullptr) {
		bool iguales = interfaz->Iguales<Cadena>(pila1, pila2, Comparador<Cadena>::Default);

		Verificar(iguales, true, sonIguales);

		pila1->Push("Lunes");
		iguales = interfaz->Iguales<Cadena>(pila1, pila2, Comparador<Cadena>::Default);
		Verificar(iguales, false, sonDistintas);

		pila2->Push("Lunes");
		iguales = interfaz->Iguales<Cadena>(pila1, pila2, Comparador<Cadena>::Default);
		Verificar(iguales, true, sonIguales);
	}
	CerrarSeccion();
}

//Operación 4:
void CasoDePrueba::PruebaOperacion4() {
	IniciarSeccion("Operacion 4a");
	Puntero<Sistema> interfaz = InicializarSistema();
	Array<Cadena> retorno;
	Array<Cadena> esperado;

	retorno = interfaz->Split("Todos los hombres son mortales", 'o');
	esperado = Array<Cadena>(7);

	esperado[0] = "T";
	esperado[1] = "d";
	esperado[2] = "s l";
	esperado[3] = "s h";
	esperado[4] = "mbres s";
	esperado[5] = "n m";
	esperado[6] = "rtales";

	VerificarSecuencias(retorno.ObtenerIterador(), esperado.ObtenerIterador(), "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");

	Array<Cadena> a1 = interfaz->Split("algooooo", 'o');
	Array<Cadena> a2 = interfaz->Split("opaaao", 'o');

	CerrarSeccion();

	IniciarSeccion("Operacion 4b");
	Cadena retorno2 = interfaz->Reverso("Quien ambiciona una corona, ignora su peso.");

	Cadena esperado2 = "peso. su ignora corona, una ambiciona Quien";

	Verificar(retorno2, esperado2, "Se verifica la operacion 4b");

	CerrarSeccion();
}

//Operación 5:
void CasoDePrueba::PruebaOperacion5() {
	IniciarSeccion("Operacion 5");
	Puntero<Sistema> interfaz = InicializarSistema();
	Cadena sonIguales = "Las listas son iguales";
	Cadena sonDistintas = "Las listas son distintas";

	Puntero<Lista<Cadena>> lista1 = interfaz->CrearListaOrdenadaEncadenada<Cadena>();
	Puntero<Lista<Cadena>> lista2 = interfaz->CrearListaOrdenadaConArray<Cadena>();

	if (lista1 == nullptr) {
		Verificar(false, true, "La lista retornada por CrearListaOrdenadaEncadenada es nula");
	} else {
		Puntero<Lista<int>> listaInt = interfaz->CrearListaOrdenadaEncadenada<int>();
		int paraInsertar = 1;

		listaInt->Insertar(paraInsertar);
		bool estaVacia = listaInt->EstaVacia();
		Verificar(estaVacia, false, "Se ingresó un elemento a la lista ordenada encadenada");

		if (!estaVacia) {
			listaInt->Eliminar(paraInsertar);
			estaVacia = listaInt->EstaVacia();
			Verificar(estaVacia, true, "Se eliminó un elemento de la lista ordenada encadenada");
		}

		int primerElementoAgregado = 2;
		int segundoElementoAgregado = 1;

		listaInt->Insertar(primerElementoAgregado);
		listaInt->Insertar(segundoElementoAgregado);

		int primerElementoEnLista = listaInt->Obtener(0);
		int segundoElementoEnLista = listaInt->Obtener(1);

		bool estaOrdenada = primerElementoEnLista == segundoElementoAgregado && segundoElementoEnLista == primerElementoAgregado;
		Verificar(estaOrdenada, true, "Se ingresa primero el 2 y después el 1 a la lista ordenada encadenada");
	}

	if (lista2 == nullptr) {
		Verificar(false, true, "La lista ordenada encadenada retornada por CrearListaOrdenadaConArray es nula");
	} else {
		Puntero<Lista<int>> listaInt = interfaz->CrearListaOrdenadaConArray<int>();
		int paraInsertar = 1;

		listaInt->Insertar(paraInsertar);
		bool estaVacia = listaInt->EstaVacia();
		Verificar(estaVacia, false, "Se ingresó un elemento a la lista ordenada con array");

		if (!estaVacia) {
			listaInt->Eliminar(paraInsertar);
			estaVacia = listaInt->EstaVacia();
			Verificar(estaVacia, true, "Se eliminó un elemento de la lista ordenada con array");
		}

		int primerElementoAgregado = 2;
		int segundoElementoAgregado = 1;

		listaInt->Insertar(primerElementoAgregado);
		listaInt->Insertar(segundoElementoAgregado);

		int primerElementoEnLista = listaInt->Obtener(0);
		int segundoElementoEnLista = listaInt->Obtener(1);

		bool estaOrdenada = primerElementoEnLista == segundoElementoAgregado && segundoElementoEnLista == primerElementoAgregado;
		Verificar(estaOrdenada, true, "Se ingresa primero el 2 y después el 1 a la lista ordenada con array");
	}

	if (lista1 != nullptr && lista2 != nullptr) {
		bool iguales = interfaz->ListasSonIguales<Cadena>(lista1, lista2, Comparador<Cadena>::Default);

		Verificar(iguales, true, sonIguales);

		lista1->Insertar("Lunes");
		iguales = interfaz->ListasSonIguales<Cadena>(lista1, lista2, Comparador<Cadena>::Default);
		Verificar(iguales, false, sonDistintas);

		lista2->Insertar("Lunes");
		iguales = interfaz->ListasSonIguales<Cadena>(lista1, lista2, Comparador<Cadena>::Default);
		Verificar(iguales, true, sonIguales);
	}
	CerrarSeccion();
}

void CasoDePrueba::PruebaOperacion6() {
	IniciarSeccion("Operacion 6");
	Puntero<Sistema> interfaz = InicializarSistema();


	Puntero<ColaPrioridad<int, int>> cp = interfaz->CrearColaPrioridad<int, int>(100);

	if (cp == nullptr) {
		Verificar(false, true, "La cola retornada por CrearColaPrioridad es nula");
	} else {
		Array<int> esperados = Array<int>(4);
		esperados[0] = 3;
		esperados[1] = 2;
		esperados[2] = 1;
		esperados[3] = 0;

		cp->Encolar(2, 20);
		bool estaVacia = cp->EstaVacia();
		Verificar(estaVacia, false, "Se ingresó un elemento el 3 con prioridad 3 a la cola");

		if (!estaVacia) {
			cp->Encolar(1, 10);
			cp->Encolar(3, 30);
			cp->Encolar(0, 0);

			Array<int> obtenidos = Array<int>(4);
			obtenidos[0] = cp->Cabeza();
			int aux = cp->Desencolar();
			Verificar(obtenidos[0] == aux, true, "El elemento retornado por Cabeza() y por Desencolar() debe ser el mismo");

			obtenidos[1] = cp->Cabeza();
			aux = cp->Desencolar();
			Verificar(obtenidos[1] == aux, true, "El elemento retornado por Cabeza() y por Desencolar() debe ser el mismo");

			obtenidos[2] = cp->Desencolar();
			obtenidos[3] = cp->Desencolar();

			VerificarSecuencias(obtenidos.ObtenerIterador(), esperados.ObtenerIterador(), "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");

			bool esperadosIgualesAObtenidos = true;
			for (unsigned int i = 0; i < esperados.ObtenerLargo(); i++) {
				esperadosIgualesAObtenidos = esperadosIgualesAObtenidos && esperados[i] == obtenidos[i];
			}
			Verificar(esperadosIgualesAObtenidos, true, "Los obtenidos deben estar en el mismo orden que los esperados(0 1 2 3)");

			estaVacia = cp->EstaVacia();
			Verificar(estaVacia, true, "Se eliminaron todos los elementos de la cola de prioridad");
		}
	}

	CerrarSeccion();
}

void CasoDePrueba::PruebaOperacion7() {
	IniciarSeccion("Operacion 7");
	Puntero<Sistema> interfaz = InicializarSistema();

	Array<int> a1 = Array<int>(5);
	a1[0] = 0;
	a1[1] = 10;
	a1[2] = 20;
	a1[3] = 30;
	a1[4] = 40;

	Array<int> a2 = Array<int>(5);
	a2[0] = 5;
	a2[1] = 15;
	a2[2] = 25;
	a2[3] = 35;
	a2[4] = 45;

	Array<int> a3 = Array<int>(5);
	a3[0] = 7;
	a3[1] = 17;
	a3[2] = 27;
	a3[3] = 28;
	a3[4] = 47;

	Array<Array<int>> entrada = Array<Array<int>>(3);
	entrada[0] = a1;
	entrada[1] = a2;
	entrada[2] = a3;

	Array<int> salidaEsperada = Array<int>(5);
	salidaEsperada[0] = 47;
	salidaEsperada[1] = 45;
	salidaEsperada[2] = 40;
	salidaEsperada[3] = 35;
	salidaEsperada[4] = 30;

	Array<int> salidaObtenida = interfaz->MayoresN<int>(entrada, Comparador<int>::Default, 5);

	if (salidaEsperada.ObtenerLargo() > salidaObtenida.ObtenerLargo()) {
		Verificar(false, true, "La salida esperada tiene más elementos que la obtenida");
	} else if (salidaEsperada.ObtenerLargo() < salidaObtenida.ObtenerLargo()) {
		Verificar(false, true, "La salida esperada tiene menos elementos que la obtenida");
	} else {
		VerificarSecuencias(salidaObtenida.ObtenerIterador(), salidaEsperada.ObtenerIterador(), "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");

		bool sonIguales = true;
		for (unsigned int i = 0; i < salidaEsperada.ObtenerLargo(); i++) {
			sonIguales = sonIguales && salidaEsperada[i] == salidaObtenida[i];
		}
		Verificar(sonIguales, true, "La salida esperada debe ser la misma que la obtenida");

	}

	CerrarSeccion();
}

void CasoDePrueba::PruebasPropias() {
	cout << endl << "+++++++++++ +++++++++++ +++++++++++ Prueba propias +++++++++++++++ ++++++++++++++++++ ++++++++" << endl;
	IniciarSeccion("Pruebas propias 1a");
	Puntero<Sistema> interfaz = InicializarSistema();
	Array<int> e1 = Array<int>(16);
	e1[0] = 14;
	e1[1] = 55;
	e1[2] = 446;
	e1[3] = 454;
	e1[4] = 554;;
	e1[5] = 555;
	e1[6] = 750;
	e1[7] = 822;
	e1[8] = 822;
	e1[9] = 1005;
	e1[10] = 1111;
	e1[11] = 1265;
	e1[12] = 1325;
	e1[13] = 1345;
	e1[14] = 1355;
	e1[15] = 1700;
	Array<int> a1 = Array<int>(16);
	a1[0] = 1355;
	a1[1] = 1111;
	a1[2] = 446;
	a1[3] = 1005;
	a1[4] = 1265;
	a1[5] = 1325;
	a1[6] = 750;
	a1[7] = 1345;
	a1[8] = 822;
	a1[9] = 555;
	a1[10] = 554;;
	a1[11] = 822;
	a1[12] = 14;
	a1[13] = 454;
	a1[14] = 55;
	a1[15] = 1700;

	interfaz->Ordenar<int>(a1, Comparador<int>::Default);

	VerificarSecuencias(a1.ObtenerIterador(), e1.ObtenerIterador(), "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");
	CerrarSeccion();

	IniciarSeccion("Pruebas propias 1b");

	Array<int> e2 = Array<int>(16);
	e2[0] = 14;
	e2[1] = 56;
	e2[2] = 446;
	e2[3] = 454;
	e2[4] = 564;
	e2[5] = 566;
	e2[6] = 750;
	e2[7] = 822;
	e2[8] = 822;
	e2[9] = 1006;
	e2[10] = 1112;
	e2[11] = 1266;
	e2[12] = 1326;
	e2[13] = 1346;
	e2[14] = 1356;
	e2[15] = 1700;
	Array<int> a2 = Array<int>(16);
	a2[0] = 1356;
	a2[1] = 1112;
	a2[2] = 446;
	a2[3] = 1006;
	a2[4] = 1266;
	a2[5] = 1326;
	a2[6] = 750;
	a2[7] = 1346;
	a2[8] = 822;
	a2[9] = 566;
	a2[10] = 564;
	a2[11] = 822;
	a2[12] = 14;
	a2[13] = 454;
	a2[14] = 56;
	a2[15] = 1700;

	interfaz->OrdenarEnteros(a2, Comparador<int>::Default);

	VerificarSecuencias(a2.ObtenerIterador(), e2.ObtenerIterador(), "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");
	CerrarSeccion();
	cout << endl << "+++++++++++ +++++++++++ +++++++++++ Fin pruebas propias +++++++++++++++ ++++++++++++++++++ ++++++++" << endl;
}
