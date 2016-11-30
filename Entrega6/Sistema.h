#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"
#include "Producto.h"

class Sistema : public ISistema
{
public:
	Sistema();

	Iterador<Tupla<nat,nat>> Laberinto(Tupla<nat,nat> &inicio, Tupla<nat,nat> &fin, Matriz<nat> &laberinto) override;

	virtual Iterador<Iterador<Puntero<ICiudad>>> Viajero(Array<Puntero<ICiudad>> &ciudadesDelMapa, Matriz<nat> &mapa, Puntero<ICiudad> &ciudadPartida, Iterador<Puntero<ICiudad>> &ciudadesPasar, nat costoMax) override;
	
	virtual Array<nat> Intercalar(Array<nat> &arreglo, nat i, nat m, nat d) override;

	virtual Array<nat> Degustacion(Array<Producto> productos, nat maxDinero, nat maxCalorias, nat maxAlcohol) override;

	//PRE: relacionesCiudades representa la matriz de adyacencia. Para un par de ciudades i,j relacionCiudades[i][j] devuelve una tupla con el costo, distancia y dinero (en ese orden) necesarios para viajar desde i hasta j.
	//POS: se retorna OK y un iterador con las ciudades a recorrer en orden.
	virtual Tupla<TipoRetorno, Iterador<nat>> Viajero2(Matriz<Tupla<nat, nat, nat>> relacionesCiudades, Iterador<nat> CiudadesPasar, Iterador<nat> CiudadesNoPasar) override;

	//PRE: recibe una array con todas las acciones posibles, indicando los recursos que se necesitan para cada accion y el impacto que tiene.
	//POST: retorna OK y un array de booleanos indicando cuántas veces realizar cada acción para maximizar el impacto.
	virtual Tupla<TipoRetorno,  Array<nat>> ProteccionAnimales(Array<Accion> acciones, nat maxVeterinarios, nat maxVehiculos, nat maxDinero, nat maxVacunas, nat maxVoluntarios) override;

	//POST: Ordena el array usando la tecnica de quicksort.
	virtual Array<nat> QuickSort(Array<nat> elementos) override;

	//PRE: pasar y noPasar son iteradores de casillas validas
	//POS: OK si existe camino. Iterador de mejores camino (cada camino se representa con un Iterador de casillas o Tuplas<int, int>)
	virtual Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>> CaminoCaballo(Tupla<int, int>& salida, Tupla<int, int>& destino, nat cantAPasar, nat tamTablero, Iterador<Tupla<int, int>>& pasar, Iterador<Tupla<int, int>>& noPasar) override;

	//PRE: semillas es un Array que contiene una Tupla de <costo siembra, agua necesaria, ganancia>
	//POS: se retorna OK, y un array indicando cantidad de hectáreas por especie.
	virtual Tupla<TipoRetorno, Array<nat>> OptimizarGranja(Array<Tupla<nat, nat, nat>>& semillas, nat dinero, nat tierra, nat agua) override;

	//PRE: matutino y nocturno representan un Iterador de Tupla<materia, creditos, horas>
	//POS: OK si existe solución y un iterador de Tupla<materia, es de turno matutino>
	virtual Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>> InscribirMaterias(Iterador<Tupla<Cadena, nat, nat>> matutino, Iterador<Tupla<Cadena, nat, nat>> nocturno, nat horasM, nat horasN) override;
private:
};

#endif
