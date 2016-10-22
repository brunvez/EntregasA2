#ifndef SISTEMA_CPP
#define SISTEMA_CPP

#include "Sistema.h"
#include "GrafoMatriz.h"
#include "CadenaFuncionHash.h"

Sistema::Sistema(nat MAX_CIUDADES) {
	costos = new GrafoMatriz<Cadena, nat>(MAX_CIUDADES, new CadenaFuncionHash(), Comparador<Cadena>::Default);
	paradas = new GrafoMatriz<Cadena, nat>(MAX_CIUDADES, new CadenaFuncionHash(), Comparador<Cadena>::Default);
	tiempos = new GrafoMatriz<Cadena, nat>(MAX_CIUDADES, new CadenaFuncionHash(), Comparador<Cadena>::Default);
	transportes = new GrafoMatriz<Cadena, TipoTransporte>(MAX_CIUDADES, new CadenaFuncionHash(), Comparador<Cadena>::Default);
}
Sistema::~Sistema() {}
TipoRetorno Sistema::AltaCiudad(const Cadena &ciudadNombre) {
	if (!costos->ExisteVertice(ciudadNombre)) {
		costos->AgregarVertice(ciudadNombre);
		paradas->AgregarVertice(ciudadNombre);
		tiempos->AgregarVertice(ciudadNombre);
		transportes->AgregarVertice(ciudadNombre);
		return OK;
	}
	return ERROR;
	return NO_IMPLEMENTADA;
}
TipoRetorno Sistema::AltaConexion(const Cadena &ciudadOrigen, const Cadena &ciudadDestino, const TipoTransporte &tipo, const nat &costo, const nat &tiempo, const nat &nroParadas) {
	if (!costos->ExisteVertice(ciudadOrigen) ||
		!costos->ExisteVertice(ciudadOrigen) ||
		costo == 0 ||
		tiempo == 0)
		return ERROR;
	costos->AgregarArco(ciudadOrigen, ciudadDestino, costo);
	paradas->AgregarArco(ciudadOrigen, ciudadDestino, nroParadas);
	tiempos->AgregarArco(ciudadOrigen, ciudadDestino, tiempo);
	transportes->AgregarArco(ciudadOrigen, ciudadDestino, tipo);
	return OK;
	return NO_IMPLEMENTADA;
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMasBarato(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenorTiempo(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosCiudades(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosTrayectosOmnibus(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosTrayectosAvion(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosParadasIntermedias(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMasBaratoOminbus(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}
#endif