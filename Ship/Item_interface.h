#ifndef ITEMINTERFACE_H
#define ITEMINTERFACE_H
#include "Imports.h"

class ItemInterface {

public:
	virtual ~ItemInterface() {};
	virtual void load(nlohmann::json data);
};


#endif