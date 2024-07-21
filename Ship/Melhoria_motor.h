#ifndef MELHORIAMOTOR_H
#define MELHORIAMOTOR_H

#include "Imports.h"
#include "Efeito.h"
#include "Item_interface.h"

class MelhoriaMotor : public ItemInterface {
public:

	int id;
	std::string nome;
	bool plus;
	float quantidade;
	std::vector<std::shared_ptr<Efeito>> efeitos;
	MelhoriaMotor();

	void load(nlohmann::json data) override;
};



#endif