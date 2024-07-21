#include "Tiro.h"


Tiro::Tiro(std::string textura_path_,sf::Vector2f posicao_inicial_,float angle_,float velocidade_):
	textura_path(textura_path_),
	posicao_inicial(posicao_inicial_),
	angle(angle_),
	velocidade(velocidade_)
{

	textura = std::make_shared<sf::Texture>();
	sprite = std::make_shared<sf::Sprite>();
	textura->loadFromFile("./resources/textures/"+textura_path);
	textura->setSmooth(true);
	sprite->setTexture(*textura);


	sprite->setTextureRect(sf::IntRect(0, 0, 128, 128));

	posicao_inicial = posicao_inicial_;
	sprite->setRotation((angle * 180 / 3.141592));
	sprite->setPosition(posicao_inicial_);	
	
	x = posicao_inicial_.x;
	y = posicao_inicial.y;

}

void Tiro::update() {
	
	x += cos(angle) * velocidade;
	y += sin(angle) * velocidade;

	sprite->setPosition(x, y);
}