#ifndef SISTEMA_CPP
#define SISTEMA_CPP

#include "Sistema.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


string Sistema::Alphabetize(string str) const {
	int i, j, flag = 1;    // set flag to 1 to start first pass
	char temp;             // holding variable
	int numLength = strlen(str.c_str());
	for (i = 1; (i <= numLength) && flag; i++) {
		flag = 0;
		for (j = 0; j < (numLength - 1); j++) {
			if (str[j + 1] < str[j]) {     // ascending order simply changes to <
				temp = str[j];             // swap elements
				str[j] = str[j + 1];
				str[j + 1] = temp;
				flag = 1;               // indicates that a swap occurred.
			}
		}
	}
	return str;   //arrays are passed to functions by address; nothing is returned
}

Sistema::Sistema() {
	fH = new FuncionHashAnagramas();
	tabla = new TablaHashAbierto<string, Puntero<NodoLista<string>>>(86011, fH, Comparador<string>(new ComparadorStrings()));
	string line;
	ifstream myfile("../../diccionario.txt", ios::in);
	//ifstream myfile("C:/Users/Bruno/Documents/GitHub/entrega1-yo/Entrega2/diccionario.txt", ios::in);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			string lineSorted = Alphabetize(line);
			int key = fH->CodigoDeHash(lineSorted);
			if (!tabla->EstaDefinida(lineSorted)) {
				Puntero<NodoLista<string>> l = new NodoLista<string>(line);
				tabla->Agregar(lineSorted, l);
			} else {
				Puntero<NodoLista<string>> dato = tabla->Obtener(lineSorted);
				dato = new NodoLista<string>(line, dato);
				tabla->Borrar(lineSorted);
				tabla->Agregar(lineSorted, dato);
			}
		}
		myfile.close();
	}
}

Sistema::~Sistema() {
}

// Ejercicio 1: Anagramas
Array<Cadena> Sistema::Anagramas(const Cadena& c) {
	string str = "";
	for (int i = 0; i < (int)c.ObtenerLargo(); i++) {
		str += tolower(c[i]);
	}
	str = Alphabetize(str);
	Puntero<NodoLista<string>> l, aux;
	l = tabla->Obtener(str);
	aux = l;
	int length = 0;
	while (aux) {
		length++;
		aux = aux->sig;
	}
	Array<Cadena> ret = Array<Cadena>(length);
	for (int i = 0; i < length; i++) {
		ret[i] = Cadena(l->dato.c_str());
		l = l->sig;
	}
	return ret;
}
#endif