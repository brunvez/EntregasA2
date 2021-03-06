﻿#pragma once

#include "Sistema.h"
#include "Prueba.h"

class CasoDePrueba : public Prueba
{
public:
	CasoDePrueba(Puntero<Sistema>(*inicializar)());

protected:
	void CorrerPruebaConcreta() override;
	Cadena GetNombre() const override;

private:
	Puntero<Sistema>(*inicializar)();
	Puntero<Sistema> InicializarSistema();

	bool ignorarOK;
	void Verificar(TipoRetorno obtenido, TipoRetorno esperado, Cadena comentario);
	template <class T>
	void Verificar(const T& obtenido, const T& esperado, Cadena comentario);
	template <class T>
	void VerificarConjuntos(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra);
	template <class T>
	void VerificarSecuencias(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra);
	template <class T>
	bool SonIguales(Iterador<T> obtenidos, Iterador<T> esperados) const;
	bool SonIguales(const Tupla<nat, nat>& obtenido, const Tupla<nat, nat>& esperado) const;
	bool SonIguales(const Cadena& obtenido, const Cadena& esperado) const;
	bool SonIguales(const bool obtenido, const bool esperado) const;
	bool SonIguales(const int obtenido, const int esperado) const;
	template <class T>
	Cadena ObtenerTexto(Iterador<T> it) const;
	Cadena ObtenerTexto(const Tupla<nat, nat>& t) const;
	Cadena ObtenerTexto(nat n) const;
	Cadena ObtenerTexto(Cadena) const;
	template <class T>
	bool Pertenece(const T& dato, Iterador<T> iterador, T& encontrado) const;

	void PruebaOperacion1();
	void PruebaOperacion2();
	void PruebaOperacion3();
	void PruebaOperacion4();
	void PruebaOperacion5();
	void PruebaOperacion6();
	void PruebaOperacion7();
	void PruebasPropias();
};
