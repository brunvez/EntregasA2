#pragma once
#include "Comparacion.h"
#include <string>
#include <assert.h>
using namespace std;

class ComparadorStrings : public Comparacion<string>{
public:
	ComparadorStrings() {};
	CompRetorno Comparar(const string& t1, const string& t2) const {
		if (t1 == t2)
			return IGUALES;
		if (t1 < t2)
			return MENOR;
		if (t1 > t2)
			return MAYOR;
		assert(false);
		return DISTINTOS;
	}
};