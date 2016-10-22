#ifndef TABLERO_CPP
#define TABLERO_CPP

#include "Tablero.h"
#include <stdio.h>
#include <string>
#include "LinkedList.h"

Tablero::Tablero(Matriz<int> bloques) {
	mat = bloques;
}

nat Tablero::PrioridadA() {
	int p = 0;
	int pos = 0;
	for (int i = 0; i < (int)mat.Largo; i++) {
		for (int j = 0; j < (int)mat[0].Largo; j++) {
			if (mat[i][j] != 0 && mat[i][j] != ++pos)
				p++;
		}
	}
	return p;
}

nat Tablero::PrioridadB() {
	int val, x, y, p;
	p = 0;
	for (int i = 0; i < (int)mat.Largo; i++) {
		for (int j = 0; j < (int)mat[0].Largo; j++) {
			val = mat[i][j];
			if (val != 0) {
				x = val / mat.Largo;
				y = val % mat.Largo - 1;
				p += abs(x - i) + abs(y - j);
			}
		}
	}
	return p;
}

bool Tablero::operator==(const Tablero& t) const {
	Matriz<int> m = t.ObtenerTablero();
	if (m.Largo != mat.Largo)
		return false;
	for (int i = 0; i < (int)mat.Largo; i++) {
		for (int j = 0; j < (int)mat.Largo; j++) {
			if (mat[i][j] != m[i][j])
				return false;
		}
	}
	return true;
}

bool Tablero::operator!=(const Tablero& t) const {
	Matriz<int> m = t.ObtenerTablero();
	if (m.Largo != mat.Largo)
		return true;
	for (int i = 0; i < (int)mat.Largo; i++) {
		for (int j = 0; j < (int)mat.Largo; j++) {
			if (mat[i][j] != m[i][j])
				return true;
		}
	}
	return false;
}


Iterador<Tablero> Tablero::Vecinos() {
	Matriz<int> m1, m2, m3, m4;
	int aux, length = (int)mat.Largo;
	Puntero<LinkedList<Tablero>> l = new LinkedList<Tablero>();
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (mat[i][j] == 0) {
				if (i - 1 >= 0) {
					m1 = CopiarMatriz(mat);
					aux = m1[i][j];
					m1[i][j] = m1[i - 1][j];
					m1[i - 1][j] = aux;
					l->AddFirst(Tablero(m1));
				}
				if (j - 1 >= 0) {
					m2 = CopiarMatriz(mat);
					aux = m2[i][j];
					m2[i][j] = m2[i][j - 1];
					m2[i][j - 1] = aux;
					l->AddFirst(Tablero(m2));
				}
				if (i + 1 < length) {
					m3 = CopiarMatriz(mat);
					aux = m3[i][j];
					m3[i][j] = m3[i + 1][j];
					m3[i + 1][j] = aux;
					l->AddFirst(Tablero(m3));
				}
				if (j + 1 < length) {
					m4 = CopiarMatriz(mat);
					aux = m4[i][j];
					m4[i][j] = m4[i][j + 1];
					m4[i][j + 1] = aux;
					l->AddFirst(Tablero(m4));
				}
				break;
			}
		}
	}
	return l->GetIterator();
	return NULL;
}

Matriz<int> Tablero::ObtenerTablero() const {
	return mat;
}

Cadena Tablero::Imprimir() const {
	int val;
	std::string str = "";
	for (int i = 0; i < (int)mat.Largo; i++) {
		str += "|";
		for (int j = 0; j < (int)mat[0].Largo; j++) {
			val = mat[i][j];
			str += std::to_string(val) + "|";
		}
		str += "\n";
	}
	const char *str_c = str.c_str();
	return Cadena(str_c);
}


Matriz<int> Tablero::CopiarMatriz(Matriz<int> original) const {
	Matriz<int> m(original.Largo);
	for (int i = 0; i < (int)original.Largo; i++) {
		for (int j = 0; j < (int)original.Largo; j++) {
			m[i][j] = original[i][j];
		}
	}
	return m;
}

#endif