#ifndef GAME_H
#define GAME_H

#include "Imports.h"
#include "Camera.h"
#include "Item.h"

class Game {
public:

	Camera camera;
	std::shared_ptr<sf::RenderWindow>window;
	sf::Texture texture;
	float x;
	float y;
	sf::Clock deltaClock;
	std::vector<std::shared_ptr<Item>> itensCarregados;

	float time;	
	void update();	
	void setClock();


	Game();

private:
	void loadItens();
};



#endif