#include "Planeta.h"


Planeta::Planeta(int id_,std::string nome_,float raio_, float massa_, sf::Color cor_, sf::Vector2f posicao_):
	id(id_),nome(nome_),raio(raio_),massa(massa_),cor(cor_),posicao(posicao_){

	circle = sf::CircleShape();	
	circle.setRadius(raio);
	circle.setFillColor(cor);
	circle.setPosition(posicao);
	circle.setOrigin(circle.getRadius() / 2, circle.getRadius() / 2);

	gravidade = raio * massa;	
}