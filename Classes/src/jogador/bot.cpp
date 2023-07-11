#include "../../include/jogador/bot.hpp"
#include <iostream>

Bot::Bot(unsigned int id): Jogador(id){
    std::srand((unsigned) time(NULL));
}

bool Bot::is_bot(){
    return true;
}

Carta* Bot::jogar_carta(unsigned int indice, Carta* carta_topo){
    Carta* carta = Jogador::jogar_carta(indice, carta_topo);
    grita_uno_aleatoriamente();
    return carta;
}

Carta* Bot::jogar_carta_apenas_pela_cor(unsigned int indice, cor curinga){
    Carta* carta = Jogador::jogar_carta_apenas_pela_cor(indice,curinga);  
    grita_uno_aleatoriamente();
    return carta;
}

void Bot::grita_uno_aleatoriamente(){
    if(get_mao()->get_numero_de_cartas() == 1){
        int chance = (rand() % 100 );
        if (chance < 80){
            set_pedir_uno(true);
        }else{
            set_pedir_uno(false);
        }
    }
}

