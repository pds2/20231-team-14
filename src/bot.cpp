#include "../include/bot.hpp"
#include <iostream>

Bot::Bot(unsigned int id){
    set_mao();
    set_id(id);
    set_humano(false);
}

Carta* Bot::jogar_carta(unsigned int indice, Carta* carta_topo){
    for(unsigned int i = indice; i < this->get_mao()->get_numero_de_cartas(); i++){
        if(verifica_carta_jogada(i, carta_topo)){
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return get_mao()->jogar_carta_selecionada(i);
        }
    }
}