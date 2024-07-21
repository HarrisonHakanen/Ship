#include "Item.h"


Item::Item(int id_, float peso_, int quantidade_, std::string textura_):
	id(id_),peso(peso_),quantidade(quantidade_),textura(textura_) {

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("./resources/textures/" + textura);
	sprite = std::make_shared<sf::Sprite>();
	sprite->setTexture(*texture);

	sprite->setTextureRect(sf::IntRect(0, 0, 152, 152));

	selecionado = false;
}


void Item::selectItem() {
	
	selecionado = true;
}

void Item::deselectItem() {
	sprite->setTextureRect(sf::IntRect(0, 0, 152, 152));
	selecionado = false;
}