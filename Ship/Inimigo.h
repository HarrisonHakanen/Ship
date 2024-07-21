#ifndef INIMIGO_H
#define INIMIGO_H

#include "Imports.h"
#include "ModeloNave.h"
#include "arma.h"


class Inimigo {
public:

	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Sprite> sprite;
	float frameVelocidade, frame, x, y, carga;
	sf::Vector2f posicao;
	sf::Vector2f escalas;
	float speed, angle, oldAngle, fireTime, fireCurrentTime, fireIncrement;
	bool Up, Down, Right, Left, Fire;
	int id, tiros_disparados;
	std::string nome;


	ModeloNave modeloNave;
	Arma arma;

	void update(float time);
	void movimentacao();
	Inimigo(sf::Vector2f posicao_, sf::Vector2f escalas_);


private:
	void load();
};



#endif