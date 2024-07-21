#include "Background.h"

Background::Background(){
	
	texture = std::make_shared<sf::Texture>();
	sprite = std::make_shared<sf::Sprite>();

	texture->loadFromFile("./resources/textures/background.jpg");
	sprite->setTexture(*texture);
}