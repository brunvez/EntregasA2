#pragma once

#include "Sistema.h"
#include "Prueba.h"
#include "Matriz.h"

class CasoDePrueba : public Prueba
{
public:
	CasoDePrueba(Puntero<Sistema>(*inicializar)(nat max));

protected:
	void CorrerPruebaConcreta() override;
	Cadena GetNombre() const override;

private:	
	nat maxVertices;
	bool ignorarOK;

	Puntero<Sistema>(*inicializar)(nat max_ciudades);
	Puntero<Sistema> InicializarSistema();

	void Verificar(TipoRetorno obtenido, TipoRetorno esperado, Cadena comentario);
	template <class T>
	void Verificar(const T& obtenido, const T& esperado, Cadena comentario);
	template <class T>
	//"Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}"
	void VerificarConjuntos(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado = "Se obtuvo {0} y se esperaba {1}", Cadena comentarioFalta = "Se esperaba {0}", Cadena comentarioSobra = "No se esperaba {0}");
	template <class T>
	void VerificarSecuencias(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado = "Se obtuvo {0} y se esperaba {1}", Cadena comentarioFalta = "Se esperaba {0}", Cadena comentarioSobra = "No se esperaba {0}");
	template <class T>
	bool SonIguales(Iterador<T> obtenidos, Iterador<T> esperados) const;
	bool SonIguales(const Tupla<nat, nat>& obtenido, const Tupla<nat, nat>& esperado) const;
	bool SonIguales(const Cadena& obtenido, const Cadena& esperado) const;
	bool SonIguales(const bool obtenido, const bool esperado) const;
	bool SonIguales(const int obtenido, const int esperado) const;
	bool SonIguales(const nat obtenido, const nat esperado) const;
	template <class T>
	Cadena ObtenerTexto(Iterador<T> it) const;
	Cadena ObtenerTexto(const Tupla<nat, nat>& t) const;
	Cadena ObtenerTexto(nat n) const;
	Cadena ObtenerTexto(int n) const;
	Cadena ObtenerTexto(Cadena) const;
	template <class T>
	bool Pertenece(const T& dato, Iterador<T> iterador, T& encontrado) const;

	Array<Cadena> InicializarGrafoCadenas(Puntero<Grafo<Cadena, int>> grafo) const;

	void VerificarArco(Puntero<Grafo<Cadena, int>> grafo, Cadena origen, Cadena destino, int arco);
	void ComprobarOrdenTopologico(const Iterador<Cadena> &orden, const Array<Cadena> &ciudades, const Matriz<bool> &precedencias);
	void Prueba1TADGrafo();
	void Prueba2TADGrafo();
};
