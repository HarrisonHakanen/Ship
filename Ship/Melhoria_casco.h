#ifndef MELHORIACASCO_H
#define MELHORIACASCO_H

#include "Imports.h"
#include "Efeito.h"
#include "Item_interface.h"

class MelhoriaCasco : public ItemInterface{
public:

	int id;
	std::string nome;
	bool plus;
	float quantidade;	
	std::vector<std::shared_ptr<Efeito>> efeitos;
	MelhoriaCasco();

	void load(nlohmann::json data) override;
};
#endif