#include "Melhoria_motor.h"
//using json = nlohmann::json;


MelhoriaMotor::MelhoriaMotor() {
}

void MelhoriaMotor::load(nlohmann::json data)  {
    
    id = data["id"].template get<int>();
    nome = data["nome"].template get<std::string>();

    for (const auto& item_json : data["efeitos"]) {
        auto efeito = std::make_shared<Efeito>();

        efeito->id = item_json["id"].template get<int>();
        efeito->nome = item_json["nome"].template get<std::string>();
        efeito->positivo = item_json["positivo"].template get<bool>();
        efeito->quantidade = item_json["quantidade"].template get<int>();

        efeitos.push_back(efeito);
    }
}