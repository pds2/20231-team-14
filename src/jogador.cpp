#include <iostream>
#include "../include/jogador.hpp"

Jogador::Jogador(std::vector<Carta*> mao){
    _numero_de_cartas_na_mao = 7;
    _mao = mao;
}

void Jogador::imprimir_mao() {
    for(Carta* c : _mao) {
        c->imprime_carta();
    }
}

Carta* Jogador::jogar_carta(unsigned int indice) {
    Carta* carta_temporaria = _mao[indice];
    _mao.erase(_mao.begin()+indice, _mao.begin()+indice+1);
    return carta_temporaria;
}





