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
void transfereItens(std::vector<std::shared_ptr<Item>>& itens1, std::vector<std::shared_ptr<Item>>& itens2, int& i);
void selecionaItens(bool select_side, int side, int side_compare, bool& right_pressed, bool& left_pressed, std::vector<std::shared_ptr<Item>>& itens1, float& button_current_time, float button_time, int i);
void renderItens(std::vector<std::shared_ptr<Item>>& itens, bool select_side, int side, int side_compare,
    int i, float& x, float& y, float x_increment, float y_increment, float x_start, std::shared_ptr <sf::RenderWindow>& window);
float itemInteract(
    bool item_find,
    std::shared_ptr <sf::RenderWindow>& window,
    sf::RectangleShape itemScreen, 
    sf::RectangleShape selectScreen, 
    std::vector<std::shared_ptr<Capsula>>capsulas, 
    Nave& nave,
    bool& e_pressed,
    bool& select_side,
    bool& right_pressed,
    bool& left_pressed,
    float& button_current_time,
    int& side,
    float button_time,
    float button_decrease_time
   );

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
    itemScreen.setOrigin(itemScreen.getSize() / 2.f);


    // Cria��o do ret�ngulo
    sf::RectangleShape selectScreen(sf::Vector2f(750.f, 1000.f));    

    // Configura��o da borda
    selectScreen.setOutlineThickness(10.f);
    selectScreen.setOutlineColor(sf::Color::White);

    // Deixar o preenchimento transparente
    selectScreen.setFillColor(sf::Color::Transparent);


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


    bool select_side = false;
    int side = 1;
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

                if (e_button_current_time <= 0) {
                    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::E)) e_pressed = true;
                }                
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left)) left_pressed = true;
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right)) right_pressed = true;
            }
        }


        if (!inventarioOption) {

            if (!pause) {

                camera.view.setCenter(nave.sprite->getPosition().x + ((nave.sprite->getTexture()->getSize().x * nave.escalas.x) / 2), nave.sprite->getPosition().y + ((nave.sprite->getTexture()->getSize().y * nave.escalas.y) / 2));
                game.window->setView(camera.view);


                //L�gicas do jogo
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

                            if (select_side) {
                                select_side = false;
                            }
                            else {
                                item_find = !item_find;
                            }

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



                //Gravidade entre nave e planetas e sistema de zoom autom�tico
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
        



        //Renderiza��es
        game.window->clear();
        game.window->draw(*background.sprite);

        for (auto planeta : planetas) {
            game.window->draw(planeta->circle);
        }

        for (auto tiro : nave.arma.tiros) {
            game.window->draw(*tiro->sprite);
        }



        for (auto capsulaAtual : capsulas) {
            game.window->draw(*capsulaAtual->sprite);
            if (capsulaAtual->showButton) {
                game.window->draw(*capsulaAtual->botao->sprite);
            }
        }

        game.window->draw(*nave.sprite);

        if (pause) {

        }


        if (inventarioOption) {
            sf::Vector2f viewCenter = game.window->getView().getCenter();
            inventoryScreen.setPosition(viewCenter);
            game.window->draw(inventoryScreen);
        }


        itemInteract(
            item_find,
            game.window,
            itemScreen,
            selectScreen,
            capsulas,
            nave,
            e_pressed,
            select_side,
            right_pressed,                
            left_pressed,                
            button_current_time,
            side,
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
    std::shared_ptr <sf::RenderWindow>& window,
    sf::RectangleShape itemScreen,
    sf::RectangleShape selectScreen,
    std::vector<std::shared_ptr<Capsula>>capsulas,
    Nave& nave,  
    bool& e_pressed,
    bool& select_side,
    bool& right_pressed,
    bool& left_pressed,
    float& button_current_time,
    int& side,
    float button_time,
    float button_decrease_time) {
    


    if (item_find) {
        sf::Vector2f viewCenter = window->getView().getCenter();
        itemScreen.setPosition(viewCenter);

        if (side == 0) {
            selectScreen.setPosition(itemScreen.getPosition().x - itemScreen.getSize().x / 2, itemScreen.getPosition().y - itemScreen.getSize().y / 2);
        }
        else if (side == 1) {
            selectScreen.setPosition(itemScreen.getPosition().x, itemScreen.getPosition().y - itemScreen.getSize().y / 2);
        }
        else {
            selectScreen.setPosition(itemScreen.getPosition().x - itemScreen.getSize().x / 2, itemScreen.getPosition().y - itemScreen.getSize().y / 2);
        }
        
        window->draw(itemScreen);
        window->draw(selectScreen);

        for (auto capsulaAtual : capsulas) {
            
            if (capsulaAtual->showButton) {


                //Mostra os itens dentro da capsula
                float x_item_start = itemScreen.getPosition().x - itemScreen.getSize().x / 2 + 50;
                float y_item_start = itemScreen.getPosition().y - itemScreen.getSize().y / 2 + 50;

                float x_item = x_item_start, y_item = y_item_start, x_increment = 50, y_increment = 50;


                for (int i = 0; i < capsulaAtual->itens.size(); i++) {

                    if (e_pressed && side == 0) {
                        
                        if (select_side) {

                            if (capsulaAtual->itens.at(i)->selecionado) {

                                if (nave.itens.size() < nave.espacos_inventario) {

                                    //Nave recebe item
                                    transfereItens(nave.itens, capsulaAtual->itens,i);                                    
                                }

                                e_pressed = false;
                                button_current_time = button_time;
                            }
                        }
                        else {
                            select_side = true;

                            e_pressed = false;
                            button_current_time = button_time;
                        }
                    }

                    selecionaItens(select_side,side,0,right_pressed,left_pressed, capsulaAtual->itens,button_current_time,button_time,i);                    
                                        
                    renderItens(capsulaAtual->itens, select_side, side, 0,i,x_item, y_item, x_increment, y_increment, x_item_start, window);                    
                }


                //Mostra os itens do player
                float x_start = itemScreen.getPosition().x + 100;
                float y_start = itemScreen.getPosition().y - itemScreen.getSize().y / 2 + 50;

                float x = x_start;
                float y = y_start;



                for (int i = 0; i < nave.itens.size(); i++) {


                    if (e_pressed && side == 1) {
                        if (select_side) {

                            if (nave.itens.at(i)->selecionado) {

                                //Capsula recebe item
                                transfereItens(capsulaAtual->itens, nave.itens, i);                                

                                e_pressed = false;
                                button_current_time = button_time;
                            }
                        }
                        else {
                            select_side = true;

                            e_pressed = false;
                            button_current_time = button_time;
                        }
                    }


                    selecionaItens(select_side, side, 1,right_pressed, left_pressed, nave.itens, button_current_time, button_time, i);
                    
                    renderItens(nave.itens, select_side, side, 1, i, x, y, x_increment, y_increment, x_start, window);                                        
                }


                if (!select_side) {
                    if (right_pressed) {

                        side = 1;
                        right_pressed = false;
                        button_current_time = button_time;
                    }
                    if (left_pressed) {

                        side = 0;
                        std::cout << side << "\n";
                        left_pressed = false;
                        button_current_time = button_time;
                    }
                }


                if (button_current_time > 0) {
                    button_current_time -= button_decrease_time;
                }
            }
        }
    }
    else {
        select_side = false;
    }
}


void transfereItens(std::vector<std::shared_ptr<Item>>& itens1, std::vector<std::shared_ptr<Item>>& itens2, int& i) {

    
    if (itens1.size() == 0) {
        itens1.emplace_back(itens2.at(i)->returnItem(true));
    }
    else {
        itens1.emplace_back(itens2.at(i)->returnItem(false));
    }
    

    itens2.erase(itens2.begin() + i);

    if (itens2.size() > 0) {
        if (i >= itens2.size()) {
            itens2.at(i - 1)->selectItem();
        }
        else {
            itens2.at(i)->selectItem();
        }
    }

    if (i == itens2.size() && itens2.size() > 0) {
        i -= 1;
    }
}


void selecionaItens(bool select_side, int side,int side_compare, bool& right_pressed, bool& left_pressed, 
    std::vector<std::shared_ptr<Item>>& itens1, float& button_current_time, float button_time,int i) {

    if (select_side && side == side_compare) {

        if (right_pressed) {

            if (itens1.at(i)->selecionado) {

                if (i + 1 < itens1.size()) {
                    itens1.at(i)->deselectItem();
                    itens1.at(i + 1)->selectItem();
                }
                else {
                    itens1.at(i)->deselectItem();
                    itens1.at(0)->selectItem();
                }

                right_pressed = false;
                button_current_time = button_time;
            }
        }


        if (left_pressed) {

            if (itens1.at(i)->selecionado) {

                if (i - 1 >= 0) {
                    itens1.at(i)->deselectItem();
                    itens1.at(i - 1)->selectItem();
                }
                else {
                    itens1.at(i)->deselectItem();
                    itens1.at(itens1.size() - 1)->selectItem();
                }

                left_pressed = false;
                button_current_time = button_time;
            }
        }
    }
}


void renderItens(std::vector<std::shared_ptr<Item>>& itens,bool select_side,int side,int side_compare,
    int i,float& x, float& y,float x_increment, float y_increment,float x_start, std::shared_ptr <sf::RenderWindow>& window) {

    if (itens.size() > 0) {

        if (select_side && side == side_compare) {
            if (itens.at(i)->selecionado) {
                itens.at(i)->sprite->setTextureRect(sf::IntRect(152, 0, 152, 152));
            }
        }
        else {
            if (itens.at(i)->selecionado) {
                itens.at(i)->sprite->setTextureRect(sf::IntRect(0, 0, 152, 152));
            }
        }

        if (i != 0 && i % 3 == 0) {
            y = y + itens.at(i)->sprite->getTexture()->getSize().y + y_increment;
            x = x_start;
        }

        itens.at(i)->sprite->setPosition(x, y);
        window->draw(*itens.at(i)->sprite);

        x += itens.at(i)->sprite->getTexture()->getSize().x / 2 + x_increment;
    }
}