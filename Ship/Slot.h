#ifndef SLOT_H
#define SLOT_H

#include "Imports.h"
#include "Item.h"

class Slot {

public:

	bool selecionado;
	int empilhamento_max;
	std::vector<std::shared_ptr<Item>> itens;
	sf::Font font;
	sf::Text qtdItensText;
	std::shared_ptr<sf::Texture> quant_texture;
	std::shared_ptr<sf::Sprite> quant_sprite;

	Slot(sf::Font font_);
};


#endif