#ifndef ITEM_H
#define ITEM_H

#include "Imports.h"
#include "Item_interface.h"

class Item {

public:
	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Sprite> sprite;
	std::string nome,textura;
	int quantidade,id,id_organizacao;	
	float peso;
	bool selecionado;
	std::shared_ptr<ItemInterface> itemReal;
	int empilhamento_max;
	Item(int id_, float peso_, int quantidade_, std::string textura_,int empilhamento_max_);
	void selectItem();
	void deselectItem();
	std::shared_ptr<Item> returnItem(bool primeiro);
};


#endif