#include "../../include/jogador/bot.hpp"
#include <iostream>

Bot::Bot(unsigned int id): Jogador(id){}

bool Bot::is_bot(){
    return true;
}

Carta* Bot::jogar_carta(unsigned int indice, Carta* carta_topo){
    std::cout << "Funcionou" << std::endl;
    Carta* carta = Jogador::jogar_carta(indice, carta_topo);
    return carta;
}

Carta* Bot::jogar_carta_apenas_pela_cor(unsigned int indice, cor curinga){
    std::cout << "Funcionou" << std::endl;
    Carta* carta = Jogador::jogar_carta_apenas_pela_cor(indice,curinga);  
    return carta;
}

