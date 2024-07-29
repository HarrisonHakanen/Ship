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
void transfereItens(std::vector<std::shared_ptr<Slot>>& slots1, std::vector<std::shared_ptr<Slot>>& slots2, int& i,bool isNave, int espacos_inventario);
void selecionaItens(bool select_side, int side, int side_compare, bool& right_pressed, bool& left_pressed, std::vector<std::shared_ptr<Slot>>& itens1, float& button_current_time, float button_time, int i);
void controleCamera(Camera& camera, bool item_find, float maxDistance, sf::Vector2f nave_posicao, float nave_peso, std::vector<std::shared_ptr<Planeta>> planetas);
void eventos(bool& pause, bool& inventarioOption, bool& item_find, bool& e_pressed, bool& left_pressed, bool& right_pressed, float e_button_current_time, std::shared_ptr<sf::RenderWindow>window);
void renderItens(std::vector<std::shared_ptr<Slot>>& slots, 
    bool select_side, int side, int side_compare,int i, float& x, float& y, float x_increment, 
    float y_increment, float x_start, std::shared_ptr <sf::RenderWindow>& window);
void distanciaItem(std::vector<std::shared_ptr<Capsula>>capsulas,
    sf::Vector2f posicaoNave, float f_button_time, float f_button_decrease_time,
    float& f_button_current_time, bool& f_pressed, bool& select_side, bool& item_find);


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

    
    sf::RectangleShape inventoryScreen(sf::Vector2f(400.f, 300.f));
    inventoryScreen.setFillColor(sf::Color(100.f, 100.f, 100.f, 200.f));
    inventoryScreen.setOrigin(inventoryScreen.getSize() / 2.0f);


    sf::RectangleShape itemScreen(sf::Vector2f(1500.f, 800.f));
    itemScreen.setFillColor(sf::Color(100.f, 100.f, 100.f, 200.f));
    itemScreen.setOrigin(itemScreen.getSize() / 2.f);
    


    // Criação do retângulo
    sf::RectangleShape selectScreen(sf::Vector2f(750.f, 800.f));    

    // Configuração da borda
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
        

        eventos(pause,inventarioOption,item_find,e_pressed,left_pressed,right_pressed,e_button_current_time,game.window);        


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
                distanciaItem(capsulas, nave.sprite->getPosition(), f_button_time, f_button_decrease_time,f_button_current_time,f_pressed,select_side,item_find);                
                //------------------------------------------------------------------------------------------


                //Gravidade entre nave e planetas e sistema de zoom automático
                controleCamera(camera, item_find, maxDistance, nave.sprite->getPosition(), nave.modeloNave.peso, planetas);                
                //-----------------------------------------------------------------------------------------  
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


        itemInteract(item_find,game.window,itemScreen,selectScreen,capsulas,nave,e_pressed,
            select_side,right_pressed,left_pressed,button_current_time,side,50,0.05);
                
        

        game.window->display();        
	}


	return 0;
}


float computeAngle(float ax, float ay, float bx, float by) {
    return atan2((by - ay), (bx - ax));
};


float itemInteract(bool item_find,std::shared_ptr <sf::RenderWindow>& window,sf::RectangleShape itemScreen,
    sf::RectangleShape selectScreen,std::vector<std::shared_ptr<Capsula>>capsulas,Nave& nave,bool& e_pressed,
    bool& select_side,bool& right_pressed,bool& left_pressed,float& button_current_time,int& side,
    float button_time,float button_decrease_time) {
    


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


                for (int i = 0; i < capsulaAtual->slots.size(); i++) {

                    if (e_pressed && side == 0) {
                        
                        if (select_side) {

                            if (capsulaAtual->slots.at(i)->selecionado) {

                                
                                //Nave recebe item
                                transfereItens(nave.slots, capsulaAtual->slots,i,true, nave.espacos_inventario);                                    
                                

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

                    selecionaItens(select_side,side,0,right_pressed,left_pressed, capsulaAtual->slots,button_current_time,button_time,i);                    
                                        
                    renderItens(capsulaAtual->slots, select_side, side, 0,i,x_item, y_item, x_increment, y_increment, x_item_start, window);                    
                }


                //Mostra os itens do player
                float x_start = itemScreen.getPosition().x + 100;
                float y_start = itemScreen.getPosition().y - itemScreen.getSize().y / 2 + 50;

                float x = x_start;
                float y = y_start;



                for (int i = 0; i < nave.slots.size(); i++) {


                    if (e_pressed && side == 1) {
                        if (select_side) {

                            if (nave.slots.at(i)->selecionado) {

                                //Capsula recebe item
                                transfereItens(capsulaAtual->slots, nave.slots, i, false, 0);                                

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


                    selecionaItens(select_side, side, 1,right_pressed, left_pressed, nave.slots, button_current_time, button_time, i);
                    
                    renderItens(nave.slots, select_side, side, 1, i, x, y, x_increment, y_increment, x_start, window);                                        
                }


                if (!select_side) {
                    if (right_pressed) {

                        side = 1;
                        right_pressed = false;
                        button_current_time = button_time;
                    }
                    if (left_pressed) {

                        side = 0;                        
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


void transfereItens(std::vector<std::shared_ptr<Slot>>& slots1, std::vector<std::shared_ptr<Slot>>& slots2, int& i, bool isNave, int espacos_inventario) {

    bool limite = false;
    if (slots1.size() == 0) {

        auto slot = std::make_shared<Slot>(slots2.at(i)->font);

        slot->itens.emplace_back(slots2.at(i)->itens.at(0)->returnItem(false));
        slot->selecionado = true;
        slot->empilhamento_max = slot->itens.at(0)->empilhamento_max;
        slots1.emplace_back(slot);
        limite = true;
    }
    else {

        auto item = slots2.at(i)->itens.at(0)->returnItem(false);
        bool encontrou = false;

        for (int j = 0; j < slots1.size(); j++) {

            if (slots1.at(j)->itens.at(0)->id == item->id) {

                if (slots1.at(j)->itens.size() < slots1.at(j)->empilhamento_max) {

                    slots1.at(j)->itens.push_back(item);
                    encontrou = true;
                    j = slots1.size();
                    limite = true;
                }
            }
        }
        if (!encontrou) {

            if (isNave) {
            
                if (slots1.size() < espacos_inventario) {
                    auto slot = std::make_shared<Slot>(slots2.at(i)->font);

                    slot->itens.push_back(item);
                    slot->selecionado = false;
                    slot->empilhamento_max = slot->itens.at(0)->empilhamento_max;
                    slots1.push_back(slot);
                    limite = true;
                }                
            }
            else {
                auto slot = std::make_shared<Slot>(slots2.at(i)->font);

                slot->itens.push_back(item);
                slot->selecionado = false;
                slot->empilhamento_max = slot->itens.at(0)->empilhamento_max;
                slots1.push_back(slot);
                limite = true;
            }            
        }        
    }
    
    if (limite) {
        slots2.at(i)->itens.erase(slots2.at(i)->itens.begin() + (slots2.at(i)->itens.size() - 1));

        if (slots2.at(i)->itens.size() == 0) {
            slots2.erase(slots2.begin() + i);
        }
    }
    


    if (slots2.size() > 0) {
        if (i >= slots2.size()) {
            slots2.at(i - 1)->itens.at(0)->selectItem();
            slots2.at(i - 1)->selecionado = true;
        }
        else {
            slots2.at(i)->itens.at(0)->selectItem();
            slots2.at(i)->selecionado = true;
        }
    }

    if (i == slots2.size() && slots2.size() > 0) {
        i -= 1;
    }
}


void selecionaItens(bool select_side, int side,int side_compare, bool& right_pressed, bool& left_pressed, 
    std::vector<std::shared_ptr<Slot>>& slots, float& button_current_time, float button_time,int i) {

    if (select_side && side == side_compare) {

        if (right_pressed) {
            
            if (slots.at(i)->selecionado) {

                if (i + 1 < slots.size()) {
                    slots.at(i)->itens.at(0)->deselectItem();
                    slots.at(i)->selecionado = false;

                    slots.at(i + 1)->itens.at(0)->selectItem();
                    slots.at(i + 1)->selecionado = true;
                }
                else {
                    slots.at(i)->itens.at(0)->deselectItem();
                    slots.at(i)->selecionado = false;

                    slots.at(0)->itens.at(0)->selectItem();
                    slots.at(0)->selecionado = true;
                }

                right_pressed = false;
                button_current_time = button_time;
            }
        }


        if (left_pressed) {
            
            if (slots.at(i)->selecionado) {
            
                if (i - 1 >= 0) {
                    slots.at(i)->itens.at(0)->deselectItem();
                    slots.at(i)->selecionado = false;

                    slots.at(i - 1)->itens.at(0)->selectItem();
                    slots.at(i - 1)->selecionado = true;
                }
                else {
                    slots.at(i)->itens.at(0)->deselectItem();
                    slots.at(i)->selecionado = false;

                    slots.at(slots.size() - 1)->itens.at(0)->selectItem();
                    slots.at(slots.size() - 1)->selecionado = true;
                }

                left_pressed = false;
                button_current_time = button_time;
            }
        }
    }
}


void renderItens(std::vector<std::shared_ptr<Slot>>& slots,
    bool select_side,int side,int side_compare, int i,float& x, float& y,float x_increment, 
    float y_increment, float x_start, std::shared_ptr <sf::RenderWindow>& window) {

    if (slots.size() > 0) {

        if (select_side && side == side_compare) {
            if (slots.at(i)->selecionado) {
                slots.at(i)->itens.at(0)->sprite->setTextureRect(sf::IntRect(152, 0, 152, 152));
            }
        }
        else {
            if (slots.at(i)->selecionado) {
                slots.at(i)->itens.at(0)->sprite->setTextureRect(sf::IntRect(0, 0, 152, 152));
            }
        }

        if (i != 0 && i % 3 == 0) {
            y = y + slots.at(i)->itens.at(0)->sprite->getTexture()->getSize().y + y_increment;
            x = x_start;
        }

        slots.at(i)->itens.at(0)->sprite->setPosition(x, y);
        
        float x_quant = x + (slots.at(i)->itens.at(0)->sprite->getTexture()->getSize().x / 2) - (slots.at(i)->quant_sprite->getTexture()->getSize().x / 2);
        float y_quant = y + (slots.at(i)->itens.at(0)->sprite->getTexture()->getSize().y) - (slots.at(i)->quant_sprite->getTexture()->getSize().y / 2);
        
        slots.at(i)->quant_sprite->setPosition(x_quant,y_quant);        
        slots.at(i)->qtdItensText.setString(std::to_string(slots.at(i)->itens.size()));
        slots.at(i)->qtdItensText.setFillColor(sf::Color::Black);
        slots.at(i)->qtdItensText.setPosition(x_quant + (slots.at(i)->quant_sprite->getTexture()->getSize().x / 2) - 10, y_quant + (slots.at(i)->quant_sprite->getTexture()->getSize().y / 2) - 20);

        

        window->draw(*slots.at(i)->itens.at(0)->sprite);
        window->draw(*slots.at(i)->quant_sprite);
        window->draw(slots.at(i)->qtdItensText);

        x += slots.at(i)->itens.at(0)->sprite->getTexture()->getSize().x / 2 + x_increment;
    }
}


void distanciaItem(std::vector<std::shared_ptr<Capsula>>capsulas,
    sf::Vector2f posicaoNave,float f_button_time, float f_button_decrease_time,
    float& f_button_current_time, bool& f_pressed,bool& select_side, bool& item_find) {


    for (auto capsulaAtual : capsulas) {

        float distancia = sqrt(pow(posicaoNave.x - capsulaAtual->sprite->getPosition().x, 2) + pow(posicaoNave.y - capsulaAtual->sprite->getPosition().y, 2));

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
}


void controleCamera(Camera& camera,bool item_find,float maxDistance,sf::Vector2f nave_posicao,float nave_peso, std::vector<std::shared_ptr<Planeta>> planetas) {

    for (auto planeta : planetas) {

        float distancia = sqrt(pow(nave_posicao.x - planeta->circle.getPosition().x, 2) + pow(nave_posicao.y - planeta->circle.getPosition().y, 2));

        float forca_gravitacional = (planeta->gravidade / distancia) * nave_peso;

        if (item_find) {
            distancia = (maxDistance + (maxDistance * forca_gravitacional) * 5);
        }

        if (distancia >= (maxDistance + (maxDistance * forca_gravitacional) * 5)) {

            //Aproxima
            if (camera.view.getSize().x >= camera.min_zoom && camera.view.getSize().y >= camera.min_zoom) {

                float newX = 0.f, newY = 0.f;

                if (item_find) {
                    newX = camera.view.getSize().x - (0.00009f * (distancia * 2));
                    newY = camera.view.getSize().y - (0.00009f * (distancia * 2));
                }
                else {
                    newX = camera.view.getSize().x - (0.00003f * (distancia * 2));
                    newY = camera.view.getSize().y - (0.00003f * (distancia * 2));
                }


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
}


void eventos(bool& pause, bool& inventarioOption, bool& item_find, bool& e_pressed, bool& left_pressed, bool& right_pressed, float e_button_current_time, std::shared_ptr<sf::RenderWindow>window) {
    sf::Event event{};

    while (window->pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            window->close();
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

            if ((e_button_current_time <= 0) && (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::E))  e_pressed = true;
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left)) left_pressed = true;
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right)) right_pressed = true;
        }
    }
}