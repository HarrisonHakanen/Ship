#include "Game.h"
#include "Resources.h"
#include <filesystem>
#include "Melhoria_casco.h"
#include "Melhoria_escudo.h"
#include "Melhoria_motor.h"
#include "Item.h"
using json = nlohmann::json;


Game::Game() {
	
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 736), "Ship", sf::Style::Titlebar | sf::Style::Close);
	window->setPosition(sf::Vector2i(0, 0));

	loadItens();
}

void Game::setClock() {
	
	time = deltaClock.getElapsedTime().asMicroseconds();
	deltaClock.restart();
	time = time / 800;		
}

void Game::loadItens() {


	std::ifstream f("resources/arquivos/itens.json");
	json data = json::parse(f);
	

	int contador = 1;
	for (const auto& item_json : data["itens"]) {


		try {

			int id = item_json.at("id").template get<int>();
			float peso = item_json.at("peso").template get<float>();
			std::string textura = item_json.at("textura").template get<std::string>();
			int empilhamento_max = item_json.at("empilhamento_max").template get<int>();
			int quantidade = 1;

			auto itemCarregado = std::make_shared<Item>(id,
				peso,
				quantidade,
				textura,
				empilhamento_max);


			if (item_json["tipo_item"]["id"].template get<int>() == 1) {

				auto melhoriaCasco = std::make_shared<MelhoriaCasco>();
				melhoriaCasco->load(item_json["item_real"]);
				itemCarregado->itemReal = melhoriaCasco;
				itensCarregados.push_back(itemCarregado);
			}
			else if (item_json["tipo_item"]["id"].template get<int>() == 2) {

				auto melhoriaMotor = std::make_shared<MelhoriaCasco>();
				melhoriaMotor->load(item_json["item_real"]);
				itemCarregado->itemReal = melhoriaMotor;
				itensCarregados.push_back(itemCarregado);
			}
			else if (item_json["tipo_item"]["id"].template get<int>() == 3) {


			}
		}
		catch (const std::exception& e) {
			std::cerr << "Erro ao criar o item: " << e.what() << std::endl;
		}			
	}
}