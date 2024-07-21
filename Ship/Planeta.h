#ifndef PLANETA_H
#define PLANETA_H

#include "Imports.h"


class Planeta {
public:

	int id;
	std::string nome, texturePath;
	float raio, massa, gravidade;
	sf::CircleShape circle;
	sf::Color cor;
	sf::Vector2f posicao;

	Planeta(int id_,std::string nome_,float raio_, float massa_, sf::Color cor_, sf::Vector2f posicao_);
};



#endif