#ifndef MOTOR_H
#define MOTOR_H

#include "Imports.h"
#include "Melhoria_motor.h"

class Motor {
public:
	int id;
	std::string nome,propelente;
	float durabilidade, degradacao,empuxo,limite_tanque,queima,resfriamento;
	std::vector<MelhoriaMotor> melhorias;
	Motor();
};



#endif