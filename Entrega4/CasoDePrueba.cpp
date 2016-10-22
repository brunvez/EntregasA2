#include "CasoDePrueba.h"
#include "CadenaFuncionHash.h"


CasoDePrueba::CasoDePrueba(Puntero<Sistema>(*inicializar)(nat max_ciudades)) {
	this->inicializar = inicializar;
	maxVertices = 20;
}

Puntero<Sistema> CasoDePrueba::InicializarSistema() {
	Puntero<Sistema> interfaz = inicializar(maxVertices);
	ignorarOK = false;
	return interfaz;
}

Cadena CasoDePrueba::GetNombre()const {
	return "Casos de Prueba";
}

void CasoDePrueba::CorrerPruebaConcreta() {
	Prueba1TADGrafo();
	Prueba2TADGrafo();
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
Cadena CasoDePrueba::ObtenerTexto(int n) const {
	nat nro = n;
	Cadena ret = ObtenerTexto(nro);
	if (n < 0) {
		ret = Cadena("-") + ret;
	}
	return ret;
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
bool CasoDePrueba::SonIguales(const nat obtenido, const nat esperado) const {
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

Array<Cadena> CasoDePrueba::InicializarGrafoCadenas(Puntero<Grafo<Cadena, int>> grafo) const {
	// Creamos datos de pruebas en el grafo
	Array<Cadena> ciudades1(5);
	ciudades1[0] = "Montevideo";
	ciudades1[1] = "Maldonado";
	ciudades1[2] = "La Paz";
	ciudades1[3] = "Salto";
	ciudades1[4] = "Durazno";

	foreach(Cadena ciudad, ciudades1.ObtenerIterador()) {
		grafo->AgregarVertice(ciudad);
	}

	// Cramos aristas de nivel 1
	grafo->AgregarArco(ciudades1[0], ciudades1[1], 10);
	grafo->AgregarArco(ciudades1[0], ciudades1[2], 17);
	grafo->AgregarArco(ciudades1[2], ciudades1[3], 1);
	grafo->AgregarArco(ciudades1[2], ciudades1[4], 3);
	grafo->AgregarArco(ciudades1[3], ciudades1[4], 10);

	return ciudades1;
}

//Operacion 1:
void CasoDePrueba::Prueba1TADGrafo() {
	IniciarSeccion("TAD Grafo");
	Puntero<Sistema> interfaz = InicializarSistema();

	Cadena mensaje = "";
	nat cantidades = 0;

	Tupla<TipoRetorno, Puntero<Grafo<Cadena, int>>> retorno =
		interfaz->CrearGrafo<Cadena, int>(maxVertices, new CadenaFuncionHash(), Comparador<Cadena>::Default);

	Verificar(retorno.Dato1, OK, "Se crea el grafo.");

	Puntero<Grafo<Cadena, int>> grafo = retorno.Dato2;
	if (grafo == nullptr) {
		Verificar(ERROR, OK, "El grafo creado es nulo.");
	} else {
		IniciarSeccion("Pruebas creacion del grafo", OK);
		Array<Cadena> ciudades = InicializarGrafoCadenas(grafo);
		CerrarSeccion();

		IniciarSeccion("Pruebas Vertices del grafo", OK);

		Verificar(grafo->CantidadVertices(), ciudades.Largo, "Cantidad de vertices esperada '{1}', obtenida '{0}'");
		cantidades = 5;
		Verificar(grafo->CantidadArcos(), cantidades, "Cantidad de arcos esperada '{1}', obtenida '{0}'");

		Cadena existeVertice = "El vertice '{0}' pertenece al grafo.";
		foreach(Cadena ciudad, ciudades.ObtenerIterador()) {
			if (grafo->ExisteVertice(ciudad)) {
				Verificar(OK, OK, existeVertice.DarFormato(ciudad));
			} else {
				Verificar(ERROR, OK, existeVertice.DarFormato(ciudad));
			}
		}

		VerificarConjuntos(grafo->Vertices(), ciudades.ObtenerIterador());

		CerrarSeccion();

		IniciarSeccion("Pruebas Adjacentes", OK);

		Cadena adj = "Cantidad de vertieces adjacentes a '{0}' {1}";
		Cadena aux = "esperado '{1}' obtenido '{0}'";
		cantidades = 2;
		Verificar(grafo->CantidadAdyacentes(ciudades[2]), cantidades, adj.DarFormato(ciudades[2], aux));
		Verificar(grafo->CantidadAdyacentes(ciudades[0]), cantidades, adj.DarFormato(ciudades[0], aux));

		Cadena incidentes = "Cantidad de vertieces incidentes a '{0}' {1}";
		Verificar(grafo->CantidadIncidentes(ciudades[4]), cantidades, incidentes.DarFormato(ciudades[4], aux));

		Array<Cadena> adjacentes(2);
		adjacentes[0] = ciudades[4];
		adjacentes[1] = ciudades[3];

		VerificarConjuntos(grafo->Adyacentes(ciudades[2]), adjacentes.ObtenerIterador());

		VerificarArco(grafo, ciudades[0], ciudades[1], 10);
		VerificarArco(grafo, ciudades[2], ciudades[3], 1);
		VerificarArco(grafo, ciudades[2], ciudades[4], 3);
		VerificarArco(grafo, ciudades[0], ciudades[2], 17);
		CerrarSeccion();
	}

	CerrarSeccion();
}

void CasoDePrueba::VerificarArco(Puntero<Grafo<Cadena, int>> grafo, Cadena origen, Cadena destino, int arcoEsperado) {
	Cadena existeArco = "Arco entre '{0} -> {1}' {2}";
	Cadena aux = "esperado '{1}' obtenido '{0}'";
	int arco = 0;

	if (grafo->ExisteArco(origen, destino)) {
		Verificar(OK, OK, existeArco.DarFormato(origen, destino, "existe"));
		arco = grafo->ObtenerArco(origen, destino);
		Verificar(arco, arcoEsperado, existeArco.DarFormato(origen, destino, aux));
	} else {
		Verificar(ERROR, OK, existeArco.DarFormato(origen, destino, "existe"));
	}
}
//Operacion 1:
void CasoDePrueba::Prueba2TADGrafo() {
	IniciarSeccion("TAD Grafo - Orden topologico");
	Puntero<Sistema> interfaz = InicializarSistema();
	Cadena mensaje = "";
	nat cantidades = 0;

	ignorarOK = true;
	Tupla<TipoRetorno, Puntero<Grafo<Cadena, int>>> retorno = interfaz->CrearGrafo<Cadena, int>(maxVertices, new CadenaFuncionHash(), Comparador<Cadena>::Default);


	Puntero<Grafo<Cadena, int>> grafo = retorno.Dato2;
	if (grafo != nullptr) {
		Array<Cadena> ciudades = InicializarGrafoCadenas(grafo);
		ignorarOK = false;

		/*
			// Cramos aristas de nivel 1
		grafo->AgregarArco(ciudades1[0], ciudades1[1], 10);
		grafo->AgregarArco(ciudades1[0], ciudades1[2], 17);
		grafo->AgregarArco(ciudades1[2], ciudades1[3], 1);
		grafo->AgregarArco(ciudades1[2], ciudades1[4], 3);
		grafo->AgregarArco(ciudades1[3], ciudades1[4], 10);
			*/
		Matriz<bool> precedencias(5);
		precedencias[0][1] = true;
		precedencias[0][2] = true;
		precedencias[2][3] = true;
		precedencias[2][4] = true;
		precedencias[3][4] = true;


		Iterador<Cadena> orden = interfaz->OrdenTopologico(grafo);
		ComprobarOrdenTopologico(orden, ciudades, precedencias);
	}
	CerrarSeccion();
}

void CasoDePrueba::ComprobarOrdenTopologico(const Iterador<Cadena> &orden, const Array<Cadena> &ciudades, const Matriz<bool> &precedencias) {
	Array<nat> indices(ciudades.Largo);
	int idx = 0;
	foreach(Cadena ciudad, orden) {
		for (nat i = 0; i < indices.Largo; i++) {
			if (ciudades[i] == ciudad) {
				indices[idx++] = i;
				break;
			}
		}
	}
	Cadena obtenido = "Se obtuvo el orden: '{0}'";

	Verificar(OK, OK, obtenido.DarFormato(ObtenerTexto(orden)));

	Cadena hayarco = "Hay un arco entre '{0}'y '{1}'";

	for (nat i = 0; i < indices.Largo; i++) {
		for (nat j = i + 1; j < indices.Largo; j++) {
			if (precedencias[indices[j]][indices[i]]) {
				Verificar(ERROR, OK, hayarco.DarFormato(ciudades[indices[j]], ciudades[indices[i]]));
			}
		}
	}
}