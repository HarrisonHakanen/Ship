#include "Button.h"


Button::Button(std::string textura,sf::Vector2f posicao,int id):
	textura(textura),id(id)
{

	texture = std::make_shared<sf::Texture>();
	sprite = std::make_shared<sf::Sprite>();
	texture->loadFromFile("./resources/textures/" + textura);
	sprite->setPosition(posicao);
	sprite->setTexture(*texture);
	sprite->setScale(1.5, 1.5);
}