#pragma once
#include "FuncionHash.h"


class FuncionHashAnagramas : public FuncionHash<string> {
public:
	inline nat CodigoDeHash(const string& str) const override {
		/*int numLength = strlen(str.c_str()); Funcion horrible
		int mul = 0;
		for (int i = 1; (i <= numLength); i++) {
			mul += ((int)str[i - 1]) * 1;
		}
		return mul;*/
		//http://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map
		int hash = 7;
		int len = strlen(str.c_str());
		for (int i = 0; i < len; i++) {
			hash = hash * 101 + str[i];
		}
		return hash;
	};
};
