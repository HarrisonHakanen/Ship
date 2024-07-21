#ifndef NAVE_H
#define NAVE_H

#include "Imports.h"
#include "ModeloNave.h"
#include "arma.h"
#include "Item.h"

class Nave {
public:

	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::Sprite> sprite;
	float frameVelocidade,frame,x,y,carga;
	sf::Vector2f posicao;
	sf::Vector2f escalas;
	float speed, angle,oldAngle;
	bool Up, Down, Right, Left,Fire;
	int id,tiros_disparados,espacos_inventario;
	std::string nome;
	std::vector<std::shared_ptr<Item>> itens;


	ModeloNave modeloNave;	
	Arma arma;

	void update(float time);
	void movimentacao();	
	Nave( sf::Vector2f posicao_,sf::Vector2f escalas_);


private:
	void load();	
};



#endif