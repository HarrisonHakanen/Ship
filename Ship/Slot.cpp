#include "Slot.h"


Slot::Slot(sf::Font font_):font(font_) {

	quant_texture = std::make_shared<sf::Texture>();
	quant_sprite = std::make_shared<sf::Sprite>();
	quant_texture->loadFromFile("./resources/textures/ItemQuantidade.png");
	quant_sprite->setTexture(*quant_texture);
	qtdItensText.setFont(font);
}