#ifndef ARMA_H
#define ARMA_H

#include "Imports.h"
#include "Tiro.h"


class Arma {

public:

	int id;
	float dano,recuperacao_atual, tempo_recuperacao,distancia_maxima,velocidade_projetil;
	float fireTime, fireCurrentTime, velocidade_disparos,peso;
	int temperatura_maxima,recuperacao_alpha, temperatura_atual, quantidade_municao;

	std::vector<std::shared_ptr<Tiro>> tiros;
	std::string textura;
	bool Fire;

	Arma();
	void update();
	void atirar(sf::Vector2f posicao, float angle);
};



#endif