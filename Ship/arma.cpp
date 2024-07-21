#include "arma.h"
#include "Tiro.h"

Arma::Arma() {

    Fire = false;
    temperatura_atual = 0;
    fireTime = 50;    
    fireCurrentTime = 0;
    recuperacao_atual = 0;
}


void Arma::update() {

    if (fireCurrentTime <= 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) Fire = true;
    }

    for (int i = 0; i < tiros.size(); i++) {

        tiros[i]->update();

        float distancia = sqrt(pow(tiros[i]->sprite->getPosition().x - tiros[i]->posicao_inicial.x, 2) + pow(tiros[i]->sprite->getPosition().y - tiros[i]->posicao_inicial.y, 2));

        if (distancia > distancia_maxima) {
            tiros.erase(tiros.begin() + i);
        }        
    }
}


void Arma::atirar(sf::Vector2f posicaoPlayer,float angle) {

    if (quantidade_municao > 0) {

        if (temperatura_atual > 0) {
            if (recuperacao_atual < recuperacao_alpha) {
                recuperacao_atual += tempo_recuperacao;
            }
            else {
                std::cout << "Tiro carregado" << "\n";
                temperatura_atual -= 1;
                recuperacao_atual = 0;
                std::cout << "Disparos disponiveis:" << std::to_string(temperatura_maxima - (int)temperatura_atual) << "\n";
                std::cout << "Quantidade municao:" << quantidade_municao << "\n\n";
            }
        }

        if (Fire) {
            std::cout << "Disparos disponiveis:" << std::to_string((temperatura_maxima - (int)temperatura_atual) - 1) << "\n";
            std::cout << "Quantidade municao:" << quantidade_municao << "\n\n";
            if (temperatura_atual < temperatura_maxima) {

                temperatura_atual += 1;

                auto tiro = std::make_shared<Tiro>(textura, posicaoPlayer, angle, velocidade_projetil);
                tiros.push_back(tiro);


                recuperacao_atual = 0;

                Fire = false;
                fireCurrentTime = fireTime;

                quantidade_municao--;
            }
        }

        if (fireCurrentTime > 0 && temperatura_atual < temperatura_maxima) {
            fireCurrentTime -= velocidade_disparos;
        }
    }
    
}