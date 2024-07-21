#ifndef MODELONAVE_H
#define MODELONAVE_H

#include "Imports.h"
#include "Casco.h"
#include "Motor.h"
#include "Escudo.h"

class ModeloNave {
public:

	int id;
	std::string nome, textura;
	float aceleracao, velocidade_max, carga, frenagem, turn_speed, peso;
	
	Escudo escudo;
	Casco casco;
	Motor motor;

	ModeloNave();

};



#endif