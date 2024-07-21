#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Imports.h"


class Background {

public:

	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Sprite> sprite;	

	Background();
};



#endif