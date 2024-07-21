#ifndef CASCO_H
#define CASCO_H

#include "Imports.h"
#include "Melhoria_casco.h"

class Casco {
public:


	float peso, resistencia_geral, durabilidade, degradacao;
	std::vector<MelhoriaCasco> melhorias;
	Casco();
};



#endif