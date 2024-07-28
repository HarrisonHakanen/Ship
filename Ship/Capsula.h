#ifndef CAPSULA_H
#define CAPSULA_H

#include "Imports.h"
#include "Item.h"
#include "Slot.h"
#include "Button.h"

class Capsula {

public:
	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Sprite> sprite;
	std::string textura;	
	sf::Font font;
	std::shared_ptr<Button> botao;
	bool showButton;	
	std::vector<std::shared_ptr<Slot>> slots;
	float rotacao,angle,velocidade;	
	Capsula(std::string textura,float rotacao,sf::Vector2f posicao, std::vector<std::shared_ptr<Item>> itensCarregados);
	void update();

};


#endif