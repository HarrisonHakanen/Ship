#ifndef BUTTON_H
#define BUTTON_H

#include "Imports.h"


class Button {

public:
	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Sprite> sprite;
	std::string textura;	
	int id;
	Button(std::string textura,sf::Vector2f posicao,int id);
};


#endif