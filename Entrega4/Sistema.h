#ifndef SISTEMA_H
#define SISTEMA_H

#include "Cadena.h"
#include "Tupla.h"
#include "Grafo.h"
#include "FuncionHash.h"
#include "Comparador.h"
#include "TipoRetorno.h"
#include "Puntero.h"
#include "Costo.h"
#include"TiposDeTransporte.h"

class Sistema {
public:
	Sistema(nat MAX_CIUDADES);
	~Sistema();
	template <class V, class A>
	Tupla<TipoRetorno, Puntero<Grafo<V, A>>> CrearGrafo(nat maxVertices, Puntero<FuncionHash<V>>, const Comparador<V>& comp);

	template <class V, class A>
	bool HayCamino(Puntero<Grafo<V, A>> g, const V& vO, const V& vD) const;

	template <class V, class A>
	TipoConexo EsConexo(Puntero<Grafo<V, A>> g) const;

	template <class V, class A>
	Iterador<V> OrdenTopologico(Puntero<Grafo<V, A>> g) const;

	template <class V, class A, typename Functor>
	Iterador<Tupla<V, V>> ArbolCubrimientoMinimo(Puntero<Grafo<V, A>> g, Functor f) const;

	template <class V, class A, typename Functor>
	Iterador<Iterador<V>> ComponentesConexas(Puntero<Grafo<V, A>> g, Functor f) const;

	template <class V, class A, typename Functor>
	Iterador<V> CaminoMasBarato(V o, V d, Puntero<Grafo<V, A>> g, Functor f) const;

	// Ejercicio 3: Grafo Ciudades


	TipoRetorno AltaCiudad(const Cadena &ciudadNombre);
	TipoRetorno AltaConexion(const Cadena &ciudadOrigen, const Cadena &ciudadDestino, const TipoTransporte &tipo, const nat &costo, const nat &tiempo, const nat &nroParadas);
	Tupla<TipoRetorno, Iterador<Cadena>> CaminoMasBarato(const Cadena &ciudadOrigen, const Cadena &ciudadDestino);
	Tupla<TipoRetorno, Iterador<Cadena>> CaminoMenorTiempo(const Cadena &ciudadOrigen, const Cadena &ciudadDestino);
	Tupla<TipoRetorno, Iterador<Cadena>> CaminoMenosCiudades(const Cadena &ciudadOrigen, const Cadena &ciudadDestino);
	Tupla<TipoRetorno, Iterador<Cadena>> CaminoMenosTrayectosOmnibus(const Cadena &ciudadOrigen, const Cadena &ciudadDestino);
	Tupla<TipoRetorno, Iterador<Cadena>> CaminoMenosTrayectosAvion(const Cadena &ciudadOrigen, const Cadena &ciudadDestino);
	Tupla<TipoRetorno, Iterador<Cadena>> CaminoMenosParadasIntermedias(const Cadena &ciudadOrigen, const Cadena &ciudadDestino);
	Tupla<TipoRetorno, Iterador<Cadena>> CaminoMasBaratoOminbus(const Cadena &ciudadOrigen, const Cadena &ciudadDestino);

	template<class V, class A>
	void aNoDirigido(Puntero<Grafo<V, A>> g) const;
private:
	Puntero<Grafo<Cadena, Tupla<TipoTransporte,int,int,int>>> caminos;
	template<class V, class A>
	bool Conexo(Puntero<Grafo<V, A>> g) const;
	
	template<class V, class A>
	bool VerticeGrado0(Puntero<Grafo<V, A>> g, V& v) const;
};

#include "SistemaTemplates.cpp"

#endif
