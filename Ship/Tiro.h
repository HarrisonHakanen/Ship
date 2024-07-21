#ifndef TIRO_H
#define TIRO_H

#include "Imports.h"

class Tiro {

public:
	float distancia_maxima, distancia_atual, angle, x, y,velocidade;
	sf::Vector2f posicao_inicial;
	std::shared_ptr<sf::Texture> textura;
	std::shared_ptr<sf::Sprite> sprite;
	std::string textura_path;

	Tiro(std::string textura_path_,sf::Vector2f posicao_inicial_,float angle_,float velocidade_);
	void update();

};


#endif