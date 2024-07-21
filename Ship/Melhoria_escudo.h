#ifndef MELHORIAESCUDO_H
#define MELHORIAESCUDO_H

#include "Imports.h"
#include "Efeito.h"

class MelhoriaEscudo {
public:

	int id;
	std::string nome;
	bool plus;
	float quantidade;
	std::shared_ptr<Efeito> efeitos;
	MelhoriaEscudo();
};



#endif