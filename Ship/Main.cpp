#include "Imports.h"
#include "Capsula.h"
#include "Game.h"
#include "Nave.h"
#include "Background.h"
#include "Planeta.h"
#include "Button.h"
#include "Melhoria_casco.h"
#include "Melhoria_motor.h"
#include "Item.h"
#include <cstdlib>


float computeAngle(float ax, float ay, float bx, float by);
float itemInteract(bool item_find,Game game,sf::RectangleShape itemScreen,std::vector<std::shared_ptr<Capsula>>capsulas,
    Nave& nave,bool& e_pressed,bool& right_pressed,bool& left_pressed,float& button_current_time,
    float button_time,float button_decrease_time);

int main() {

    std::srand(std::time(0));
    
	Game game;    
	Camera camera;
	game.window->setView(camera.view);
    

    std::vector<std::shared_ptr<Capsula>>capsulas;
    std::shared_ptr<Capsula> capsula = std::make_shared<Capsula>("Item1.png", 0.0005,sf::Vector2f(0,0),game.itensCarregados);    
    std::shared_ptr<Capsula> capsula2 = std::make_shared<Capsula>("Item1.png", 0.0005, sf::Vector2f(1000, 500),game.itensCarregados);
    std::shared_ptr<Capsula> capsula3 = std::make_shared<Capsula>("Item1.png", 0.0005, sf::Vector2f(200, 500),game.itensCarregados);

    

    capsulas.emplace_back(capsula);
    capsulas.emplace_back(capsula2);
    capsulas.emplace_back(capsula3);


    Nave nave(sf::Vector2f(20,20),sf::Vector2f(0.3,0.3));
    Background background;

    
    float maxDistance = 3000.f;
    bool pause = false, inventarioOption = false,item_find = false;

    
    sf::RectangleShape inventoryScreen(sf::Vector2f(400, 300));
    inventoryScreen.setFillColor(sf::Color(100, 100, 100, 200));
    inventoryScreen.setOrigin(inventoryScreen.getSize() / 2.0f);


    sf::RectangleShape itemScreen(sf::Vector2f(1500, 1000));
    itemScreen.setFillColor(sf::Color(100, 100, 100, 200));
    itemScreen.setOrigin(itemScreen.getSize() / 2.0f);


    std::vector<std::shared_ptr<Planeta>> planetas;
    std::shared_ptr<Planeta> planeta2 = std::make_shared<Planeta>(2,"Planeta2",200.f, 0.8f, sf::Color::Blue, sf::Vector2f(3000, 8000));
    std::shared_ptr<Planeta> planeta3 = std::make_shared<Planeta>(3,"Planeta3",500.f, 0.8f, sf::Color::Red, sf::Vector2f(3000, 3000));
    planetas.push_back(planeta2);
    planetas.push_back(planeta3);


    bool f_pressed = false;
    float f_button_time = 50;
    float f_button_current_time = 0;
    float f_button_decrease_time = 0.07;

    

    bool left_pressed = false;
    float left_button_current_time = 0;
   
    bool right_pressed = false;    
    float right_button_current_time = 0;    

    bool e_pressed = false;
    float e_button_current_time = 0;

    float button_current_time = 0;

    
	while (game.window->isOpen()) {


        game.setClock();

        sf::Event event{};

        while (game.window->pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                game.window->close();
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
            {                  
                pause = !pause;
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::I))
            {   
                if (!pause) {
                    inventarioOption = !inventarioOption;
                }                
            }

            if (item_find) {                
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::E)) e_pressed = true;
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left)) left_pressed = true;
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right)) right_pressed = true;
            }
        }


        if (!inventarioOption) {

            if (!pause) {

                camera.view.setCenter(nave.sprite->getPosition().x + ((nave.sprite->getTexture()->getSize().x * nave.escalas.x) / 2), nave.sprite->getPosition().y + ((nave.sprite->getTexture()->getSize().y * nave.escalas.y) / 2));
                game.window->setView(camera.view);




                //Lógicas do jogo
                if (!item_find) {

                    nave.movimentacao();
                    nave.update(game.time);

                    for (auto capsulaAtual : capsulas) {
                        capsulaAtual->update();
                    }
                }
                



                //Verifica itens por perto e se foi interagido com o item

                for (auto capsulaAtual : capsulas) {

                    float distancia = sqrt(pow(nave.sprite->getPosition().x - capsulaAtual->sprite->getPosition().x, 2) + pow(nave.sprite->getPosition().y - capsulaAtual->sprite->getPosition().y, 2));

                    if (distancia < 300) {


                        if (f_button_current_time <= 0) {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) f_pressed = true;
                        }
                        
                        if (f_pressed)
                        {                                                        
                            item_find = !item_find;                            
                            
                            f_pressed = false;
                            f_button_current_time = f_button_time;
                        }


                        capsulaAtual->showButton = true;
                    }
                    else {
                        capsulaAtual->showButton = false;
                    }                    
                }

                if (f_button_current_time > 0) {
                    f_button_current_time = f_button_current_time - f_button_decrease_time;
                }
                //------------------------------------------------------------------------------------------



                //Gravidade entre nave e planetas e sistema de zoom automático
                for (auto planeta : planetas) {

                    float distancia = sqrt(pow(nave.sprite->getPosition().x - planeta->circle.getPosition().x, 2) + pow(nave.sprite->getPosition().y - planeta->circle.getPosition().y, 2));

                    float forca_gravitacional = (planeta->gravidade / distancia) * nave.modeloNave.peso;


                    if (distancia >= (maxDistance + (maxDistance * forca_gravitacional) * 5)) {

                        //Aproxima
                        if (camera.view.getSize().x >= camera.min_zoom && camera.view.getSize().y >= camera.min_zoom) {

                            float newX = camera.view.getSize().x - (0.00003f * (distancia * 2));
                            float newY = camera.view.getSize().y - (0.00003f * (distancia * 2));

                            camera.view.setSize(newX, newY);
                        }
                    }
                    else {

                        //Afasta
                        if (camera.view.getSize().x <= camera.max_zoom && camera.view.getSize().y <= camera.max_zoom) {

                            float newX = camera.view.getSize().x + (0.0003f * (distancia * 2));
                            float newY = camera.view.getSize().y + (0.0003f * (distancia * 2));

                            camera.view.setSize(newX, newY);
                        }
                    }


                    /*
                    if (forca_gravitacional > 0.02) {

                        float angulo = computeAngle(nave.sprite->getPosition().x, nave.sprite->getPosition().y, planeta->circle.getPosition().x, planeta->circle.getPosition().y);

                        nave.x += cos(angulo) * forca_gravitacional;
                        nave.y += sin(angulo) * forca_gravitacional;

                        nave.sprite->setPosition(nave.x, nave.y);

                    }
                    */
                }
                //------------------------------------------------------------------------------------------

                
            }            
        }
        



        //Renderizações
        game.window->clear();
        game.window->draw(*background.sprite);

        for (auto planeta : planetas) {
            game.window->draw(planeta->circle);
        }

        for (auto tiro : nave.arma.tiros) {
            game.window->draw(*tiro->sprite);
        }



        game.window->draw(*nave.sprite);

        for (auto capsulaAtual : capsulas) {
            game.window->draw(*capsulaAtual->sprite);
            if (capsulaAtual->showButton) {
                game.window->draw(*capsulaAtual->botao->sprite);
            }
        }

        if (pause) {

        }


        if (inventarioOption) {
            sf::Vector2f viewCenter = game.window->getView().getCenter();
            inventoryScreen.setPosition(viewCenter);
            game.window->draw(inventoryScreen);
        }


            itemInteract(
                item_find,
                game,
                itemScreen,
                capsulas,
                nave,
                e_pressed,                
                right_pressed,                
                left_pressed,                
                button_current_time,
                50,
                0.05);
        
        
        game.window->display();
        
	}


	return 0;
}


float computeAngle(float ax, float ay, float bx, float by) {
    return atan2((by - ay), (bx - ax));
};


float itemInteract(
    bool item_find,
    Game game,
    sf::RectangleShape itemScreen,
    std::vector<std::shared_ptr<Capsula>>capsulas,
    Nave& nave,  
    bool& e_pressed,
    bool& right_pressed,
    bool& left_pressed,
    float& button_current_time,
    float button_time,
    float button_decrease_time) {
    


    if (item_find) {
        sf::Vector2f viewCenter = game.window->getView().getCenter();
        itemScreen.setPosition(viewCenter);
        game.window->draw(itemScreen);

        for (auto capsulaAtual : capsulas) {
            
            if (capsulaAtual->showButton) {


                //Mostra os itens dentro da capsula
                float x_item_start = itemScreen.getPosition().x - itemScreen.getSize().x / 2 + 50;
                float y_item_start = itemScreen.getPosition().y - itemScreen.getSize().y / 2 + 50;

                float x_item = x_item_start, y_item = y_item_start, x_increment = 50, y_increment = 50;


                for (int i = 0; i < capsulaAtual->itens.size(); i++) {


                    if (e_pressed) {
                        if (capsulaAtual->itens.at(i)->selecionado) {

                            if (nave.itens.size() < nave.espacos_inventario) {

                                nave.itens.emplace_back(capsulaAtual->itens.at(i));
                                capsulaAtual->itens.erase(capsulaAtual->itens.begin() + i);

                                if (capsulaAtual->itens.size() > 0) {
                                    capsulaAtual->itens.at(0)->selectItem();
                                }

                                if (i == capsulaAtual->itens.size() && capsulaAtual->itens.size() > 0) {
                                    i -= 1;
                                }
                            }

                            e_pressed = false;
                        }
                    }

                    
                    if (right_pressed) {
                        if (capsulaAtual->itens.at(i)->selecionado) {

                            if (i + 1 < capsulaAtual->itens.size()) {
                                capsulaAtual->itens.at(i)->deselectItem();
                                capsulaAtual->itens.at(i + 1)->selectItem();                                
                            }
                            else {
                                capsulaAtual->itens.at(i)->deselectItem();
                                capsulaAtual->itens.at(0)->selectItem();
                            }

                            right_pressed = false;
                        }

                        button_current_time = button_time;
                    }


                    if (left_pressed) {
                        if (capsulaAtual->itens.at(i)->selecionado) {

                            if (i - 1 >= 0) {
                                capsulaAtual->itens.at(i)->deselectItem();
                                capsulaAtual->itens.at(i - 1)->selectItem();
                            }
                            else {
                                capsulaAtual->itens.at(i)->deselectItem();
                                capsulaAtual->itens.at(capsulaAtual->itens.size()-1)->selectItem();
                            }

                            

                            left_pressed = false;
                        }

                        button_current_time = button_time;
                    }
                    
                    if (capsulaAtual->itens.size() > 0) {


                        if (capsulaAtual->itens.at(i)->selecionado) {
                            capsulaAtual->itens.at(i)->sprite->setTextureRect(sf::IntRect(152, 0, 152, 152));
                        }


                        if (i != 0 && i % 3 == 0) {
                            y_item = y_item + capsulaAtual->itens.at(i)->sprite->getTexture()->getSize().y + y_increment;
                            x_item = x_item_start;
                        }


                        capsulaAtual->itens.at(i)->sprite->setPosition(x_item, y_item);
                        game.window->draw(*capsulaAtual->itens.at(i)->sprite);

                        x_item += capsulaAtual->itens.at(i)->sprite->getTexture()->getSize().x / 2 + x_increment;
                    }                                        
                }




                //Mostra os itens do player
                float x_start = itemScreen.getPosition().x + 100;
                float y_start = itemScreen.getPosition().y - itemScreen.getSize().y / 2 + 50;

                float x = x_start;
                float y = y_start;



                for (int i = 0; i < nave.itens.size(); i++) {

                    if (i != 0 && i % 3 == 0) {
                        y = y + nave.itens.at(i)->sprite->getTexture()->getSize().y + y_increment;
                        x = x_start;
                    }

                    nave.itens.at(i)->sprite->setPosition(x, y);
                    game.window->draw(*nave.itens.at(i)->sprite);

                    x += nave.itens.at(i)->sprite->getTexture()->getSize().x / 2 + x_increment;
                }
            }
        }
    }
}
