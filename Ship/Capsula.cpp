#include "Capsula.h"
#include "Melhoria_casco.h"
#include "Melhoria_escudo.h"
#include "Melhoria_motor.h"
using json = nlohmann::json;


Capsula::Capsula(std::string textura_, float rotacao_,sf::Vector2f posicao, std::vector<std::shared_ptr<Item>> itensCarregados):
	textura(textura_),rotacao(rotacao_)
{	

	showButton = false;
	texture = std::make_shared<sf::Texture>();
	sprite = std::make_shared<sf::Sprite>();
	texture->loadFromFile("./resources/textures/"+textura);
	sprite->setPosition(posicao);	
	sprite->setTexture(*texture);

	float origemX = sprite->getTexture()->getSize().x / 2;
	float origemY = sprite->getTexture()->getSize().y / 2;

	sprite->setOrigin(origemX,origemY);

	botao = std::make_shared<Button>("Button_f.png", posicao, 0);
	botao->sprite->setPosition(sprite->getPosition().x + sprite->getTexture()->getSize().x/2, sprite->getPosition().y + sprite->getTexture()->getSize().y/2);		




	int qtdMinimaItens = 1;
	int qtdMaximaItens = 8;

	int qtdItens = qtdMinimaItens + (std::rand() % (qtdMaximaItens - qtdMinimaItens + 1));

	for (int i = 0; i < qtdItens; i++) {

		int idTipoItemInicio = 1;
		int idTipoItemFim = 4;
		

		int idTipoItem = idTipoItemInicio + (std::rand() % (idTipoItemFim - idTipoItemInicio + 1));


		for (int j = 0; j < itensCarregados.size(); j++) {

			if (idTipoItem == itensCarregados.at(j)->id) {				
				

				int quantidade = 1;

				auto item = std::make_shared<Item>(itensCarregados.at(j)->id,
					itensCarregados.at(j)->peso,
					quantidade,
					itensCarregados.at(j)->textura);

												
				itens.emplace_back(item);
				j = itensCarregados.size();
			}
		}
	}
	
	itens.at(0)->selectItem();
}


void Capsula::update() {

	angle += rotacao;
	sprite->setRotation(angle * 180 / 3.141592);

	botao->sprite->setPosition(sprite->getPosition().x + sprite->getTexture()->getSize().x / 2, sprite->getPosition().y + sprite->getTexture()->getSize().y / 2);
}