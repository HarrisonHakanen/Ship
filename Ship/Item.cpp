#include "Item.h"


Item::Item(int id_, float peso_, int quantidade_, std::string textura_,int empilhamento_max_):
	id(id_),peso(peso_),quantidade(quantidade_),textura(textura_),empilhamento_max(empilhamento_max_) {

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("./resources/textures/" + textura);
	sprite = std::make_shared<sf::Sprite>();
	sprite->setTexture(*texture);

	sprite->setTextureRect(sf::IntRect(0, 0, 152, 152));

	selecionado = false;
}


void Item::selectItem() {
	sprite->setTextureRect(sf::IntRect(152, 0, 152, 152));
	selecionado = true;
}

void Item::deselectItem() {
	sprite->setTextureRect(sf::IntRect(0, 0, 152, 152));
	selecionado = false;
}

std::shared_ptr<Item> Item::returnItem(bool primeiro) {

	std::shared_ptr<Item> itemReturn = std::make_shared<Item>(id,peso,quantidade,textura, empilhamento_max);

	itemReturn->id_organizacao = id_organizacao;	
	itemReturn->itemReal = itemReal;		
	itemReturn->nome = nome;
	itemReturn->empilhamento_max = empilhamento_max;

	if (primeiro) {
		itemReturn->sprite->setTextureRect(sf::IntRect(152, 0, 152, 152));
		itemReturn->selecionado = true;
	}


	return itemReturn;
}