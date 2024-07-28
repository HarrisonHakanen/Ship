#include "Nave.h"
using json = nlohmann::json;


Nave::Nave(sf::Vector2f posicao_,sf::Vector2f escalas_):
    frameVelocidade(0.009f),
    escalas(escalas_)
{    

    load();

    tiros_disparados = 0;
    speed = 0.f;
    angle = 0.f;
    oldAngle = angle;  

    Up = false;
    Down = false;
    Right = false;
    Left = false;
    Fire = false;    
    
    posicao = posicao_;
	texture = std::make_shared<sf::Texture>();
	sprite = std::make_shared<sf::Sprite>();
	texture->loadFromFile("./resources/textures/"+modeloNave.textura);
    texture->setSmooth(true);
    sprite->setPosition(posicao_);    
	sprite->setTexture(*texture);
    sprite->setScale(escalas);
    
    

    sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);


    x = sprite->getPosition().x;
    y = sprite->getPosition().y;

	frame = 0.f;

    
}


void Nave::movimentacao() {

    Up = false;
    Down = false;
    Right = false;
    Left = false;
    

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) Right = true;    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) Left = true;   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) Up = true;    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) Down = true;   
}

void Nave::update(float time) {
    

    if(Up && speed < modeloNave.velocidade_max) {
        if (speed < 0) speed += modeloNave.frenagem;
        else speed += modeloNave.aceleracao;
    }
    if (Down && speed >-modeloNave.velocidade_max) {
        if (speed > 0) speed -= modeloNave.frenagem;
        else speed -= modeloNave.aceleracao;
    }
    if (!Up && !Down) {
        if (speed - modeloNave.frenagem > 0) speed -= modeloNave.frenagem;
        else if (speed + modeloNave.frenagem < 0) speed += modeloNave.frenagem;
        else speed = 0;
    }
    
    
    if (Right) angle += modeloNave.turn_speed;
    if (Left) angle -= modeloNave.turn_speed;
    
    if (!Up && speed > 0) {
        
        x += cos(oldAngle) * speed;
        y += sin(oldAngle) * speed;


        sprite->setPosition(x, y);
        sprite->setRotation(angle * 180 / 3.141592);
    }
    else {
        x += cos(angle) * speed;
        y += sin(angle) * speed;


        sprite->setPosition(x, y);
        sprite->setRotation(angle * 180 / 3.141592);

        oldAngle = angle;
    }    
    
    
    //update da arma
    arma.atirar(sprite->getPosition(),angle);
    arma.update();
}


void Nave::load() {

    std::ifstream f("resources/arquivos/player.json");
    json data = json::parse(f);
    font.loadFromFile("./resources/fonts/Minecraft.ttf");

    if (data["player"].contains("slots") && data["player"]["slots"].is_array()) {

        for (const auto& slotJson : data["player"]["slots"]) {

            auto slot = std::make_shared<Slot>(font);


            if (slotJson["itens"].is_array()) {

                for (const auto& item_json : slotJson["itens"]) {

                    int id = item_json.at("id").template get<int>();
                    float peso = item_json.at("peso").template get<float>();
                    int empilhamento_max = item_json.at("empilhamento_max").template get<int>();

                    std::string textura = item_json.at("textura").template get<std::string>();
                    int quantidade = 1;
                    
                    auto item = std::make_shared<Item>(id,
                        peso,
                        quantidade,
                        textura,
                        empilhamento_max);


                    if (item_json["tipo_item"]["id"].template get<int>() == 1) {

                        auto melhoriaCasco = std::make_shared<MelhoriaCasco>();
                        melhoriaCasco->load(item_json["item_real"]);
                        item->itemReal = melhoriaCasco;
                        slot->itens.push_back(item);
                    }
                    else if (item_json["tipo_item"]["id"].template get<int>() == 2) {

                        auto melhoriaMotor = std::make_shared<MelhoriaCasco>();
                        melhoriaMotor->load(item_json["item_real"]);
                        item->itemReal = melhoriaMotor;
                        slot->itens.push_back(item);
                    }
                    else if (item_json["tipo_item"]["id"].template get<int>() == 3) {
                    }
                }
            }

            slot->empilhamento_max = slot->itens.at(0)->empilhamento_max;
            slot->font = font;    
            slot->selecionado = false;
            slots.push_back(slot);
        }
    }

    if (slots.size() > 0) {
        slots.at(0)->selecionado = true;
    }
    
    //itens.at(0)->selecionado = true;


    id = data["player"]["id"].template get<int>();
    nome = data["player"]["nome"].template get<std::string>();
    espacos_inventario = data["player"]["espacos_inventario"].template get<int>();

    modeloNave.id = data["player"]["modelo_nave"]["id"].template get<int>();
    modeloNave.nome = data["player"]["modelo_nave"]["nome"].template get<std::string>();
    modeloNave.textura = data["player"]["modelo_nave"]["textura"].template get<std::string>();
    modeloNave.aceleracao = data["player"]["modelo_nave"]["aceleracao"].template get<float>();
    modeloNave.velocidade_max = data["player"]["modelo_nave"]["velocidade_max"].template get<float>();
    modeloNave.carga = data["player"]["modelo_nave"]["carga"].template get<float>();
    modeloNave.frenagem = data["player"]["modelo_nave"]["frenagem"].template get<float>();
    modeloNave.turn_speed = data["player"]["modelo_nave"]["turn_speed"].template get<float>();
    modeloNave.peso = data["player"]["modelo_nave"]["peso"].template get<float>();

    arma.dano = data["player"]["arma"]["dano"].template get<float>();
    arma.textura = data["player"]["arma"]["texture"].template get<std::string>();
    arma.temperatura_maxima = data["player"]["arma"]["temperatura_maxima"].template get<int>();
    arma.tempo_recuperacao = data["player"]["arma"]["tempo_recuperacao"].template get<float>();
    arma.recuperacao_alpha = data["player"]["arma"]["recuperacao_alpha"].template get<int>();
    arma.distancia_maxima = data["player"]["arma"]["distancia_maxima"].template get<float>();
    arma.velocidade_projetil = data["player"]["arma"]["velocidade_projetil"].template get<float>();
    arma.velocidade_disparos = data["player"]["arma"]["velocidade_disparos"].template get<float>();
    arma.peso = data["player"]["arma"]["peso"].template get<float>();
    arma.quantidade_municao = data["player"]["arma"]["quantidade_municao"].template get<int>();

    modeloNave.escudo.id = data["player"]["modelo_nave"]["escudo"]["id"].template get<int>();
    modeloNave.escudo.durabilidade = data["player"]["modelo_nave"]["escudo"]["durabilidade"].template get<float>();
    modeloNave.escudo.degradacao = data["player"]["modelo_nave"]["escudo"]["degradacao"].template get<float>();
    modeloNave.escudo.peso = data["player"]["modelo_nave"]["escudo"]["peso"].template get<float>();

    modeloNave.casco.peso = data["player"]["modelo_nave"]["casco"]["peso"].template get<float>();
    modeloNave.casco.resistencia_geral = data["player"]["modelo_nave"]["casco"]["resistencia_geral"].template get<float>();
    modeloNave.casco.durabilidade = data["player"]["modelo_nave"]["casco"]["durabilidade"].template get<float>();
    modeloNave.casco.degradacao = data["player"]["modelo_nave"]["casco"]["degradacao"].template get<float>();

    modeloNave.motor.id = data["player"]["modelo_nave"]["motor"]["id"].template get<int>();
    modeloNave.motor.durabilidade = data["player"]["modelo_nave"]["motor"]["durabilidade"].template get<float>();
    modeloNave.motor.degradacao = data["player"]["modelo_nave"]["motor"]["degradacao"].template get<float>();
    modeloNave.motor.nome = data["player"]["modelo_nave"]["motor"]["nome"].template get<std::string>();
    modeloNave.motor.empuxo = data["player"]["modelo_nave"]["motor"]["empuxo"].template get<float>();
    modeloNave.motor.propelente = data["player"]["modelo_nave"]["motor"]["propelente"].template get<std::string>();
    modeloNave.motor.limite_tanque = data["player"]["modelo_nave"]["motor"]["limite_tanque"].template get<float>();
    modeloNave.motor.queima = data["player"]["modelo_nave"]["motor"]["queima"].template get<float>();
    modeloNave.motor.resfriamento = data["player"]["modelo_nave"]["motor"]["resfriamento"].template get<float>();
}