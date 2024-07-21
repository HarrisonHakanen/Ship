#ifndef ESCUDO_H
#define ESCUDO_H

#include "Imports.h"
#include "Melhoria_escudo.h"

class Escudo {
public:
	int id;
	float durabilidade, degradacao, peso, protecao;
	std::vector<MelhoriaEscudo> melhorias;
	Escudo();
};

#endif