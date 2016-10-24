#ifndef SISTEMA_CPP
#define SISTEMA_CPP

#include "Sistema.h"
#include "GrafoMatriz.h"
#include "CadenaFuncionHash.h"

Sistema::Sistema(nat MAX_CIUDADES) {
	caminos = new GrafoMatriz<Cadena, Tupla<TipoTransporte, int, int, int>>(MAX_CIUDADES, new CadenaFuncionHash(), Comparador<Cadena>::Default);
}

Sistema::~Sistema() {}

TipoRetorno Sistema::AltaCiudad(const Cadena &ciudadNombre) {
	if (!caminos->ExisteVertice(ciudadNombre)) {
		caminos->AgregarVertice(ciudadNombre);
		return OK;
	}
	return ERROR;
	return NO_IMPLEMENTADA;
}

TipoRetorno Sistema::AltaConexion(const Cadena &ciudadOrigen, const Cadena &ciudadDestino, const TipoTransporte &tipo, const nat &costo, const nat &tiempo, const nat &nroParadas) {
	if (costo == 0 || tiempo == 0)
		return ERROR;
	Tupla<TipoTransporte, int, int, int> a(tipo, costo, tiempo, nroParadas);
	if (caminos->ExisteVertice(ciudadOrigen) && caminos->ExisteVertice(ciudadDestino) && !caminos->ExisteArco(ciudadOrigen, ciudadDestino)) {
		caminos->AgregarArco(ciudadOrigen, ciudadDestino, a);
		return OK;
	}
	return ERROR;
	return NO_IMPLEMENTADA;
}

Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMasBarato(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	auto f = [](Tupla<TipoTransporte, int, int, int> t)->Costo {
		return Costo(Tupla<int, int, int, int>(t.Dato2, t.Dato3, 1, 0));
	};
	if (!caminos->ExisteVertice(ciudadOrigen) || !caminos->ExisteVertice(ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!HayCamino(caminos, ciudadOrigen, ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, CaminoMasBarato(ciudadOrigen, ciudadDestino, caminos, f));
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}

Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenorTiempo(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	auto f = [](Tupla<TipoTransporte, int, int, int> t)->Costo {
		return Costo(Tupla<int, int, int, int>(t.Dato3, t.Dato2, 1, 0));
	};
	if (!caminos->ExisteVertice(ciudadOrigen) || !caminos->ExisteVertice(ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!HayCamino(caminos, ciudadOrigen, ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, CaminoMasBarato(ciudadOrigen, ciudadDestino, caminos, f));
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}

Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosCiudades(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	auto f = [](Tupla<TipoTransporte, int, int, int> t)->Costo {
		return Costo(Tupla<int, int, int, int>(1, t.Dato4, 0, 0));
	};
	if (!caminos->ExisteVertice(ciudadOrigen) || !caminos->ExisteVertice(ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!HayCamino(caminos, ciudadOrigen, ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, CaminoMasBarato(ciudadOrigen, ciudadDestino, caminos, f));
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}

Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosTrayectosOmnibus(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	auto f = [](Tupla<TipoTransporte, int, int, int> t)->Costo {
		if(t.Dato1 == OMNIBUS)
			return Costo(Tupla<int, int, int, int>(1, t.Dato3, 0, 0));
		return Costo(Tupla<int, int, int, int>(0, t.Dato3, 0, 0));
	};
	if (!caminos->ExisteVertice(ciudadOrigen) || !caminos->ExisteVertice(ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!HayCamino(caminos, ciudadOrigen, ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, CaminoMasBarato(ciudadOrigen, ciudadDestino, caminos, f));
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}

Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosTrayectosAvion(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	auto f = [](Tupla<TipoTransporte, int, int, int> t)->Costo {
		if (t.Dato1 == AVION)
			return Costo(Tupla<int, int, int, int>(1, t.Dato3, 0, 0));
		return Costo(Tupla<int, int, int, int>(0, t.Dato3, 0, 0));
	};
	if (!caminos->ExisteVertice(ciudadOrigen) || !caminos->ExisteVertice(ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!HayCamino(caminos, ciudadOrigen, ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, CaminoMasBarato(ciudadOrigen, ciudadDestino, caminos, f));
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}

Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosParadasIntermedias(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	auto f = [](Tupla<TipoTransporte, int, int, int> t)->Costo {
		return Costo(Tupla<int, int, int, int>(t.Dato4, t.Dato2, 0, 0));
	};
	if (!caminos->ExisteVertice(ciudadOrigen) || !caminos->ExisteVertice(ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!HayCamino(caminos, ciudadOrigen, ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, CaminoMasBarato(ciudadOrigen, ciudadDestino, caminos, f));
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}

Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMasBaratoOminbus(const Cadena &ciudadOrigen, const Cadena &ciudadDestino) {
	auto f = [](Tupla<TipoTransporte, int, int, int> t)->Costo {
		if (t.Dato1 == OMNIBUS)
			return  Costo(Tupla<int, int, int, int>(t.Dato2, 1, t.Dato3, 0));
		return Costo(Tupla<int, int, int, int>(t.Dato2, 0, t.Dato3, 0));
	};
	if (!caminos->ExisteVertice(ciudadOrigen) || !caminos->ExisteVertice(ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!HayCamino(caminos, ciudadOrigen, ciudadDestino))
		return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, CaminoMasBarato(ciudadOrigen, ciudadDestino, caminos, f));
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, nullptr);
}
#endif