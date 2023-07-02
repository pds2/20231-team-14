#include <iostream>
#include "../include/jogador.hpp"

Jogador::Jogador(unsigned int id){
    _mao = new MaoJogador();
    _id = id;
}

void Jogador::receber_cartas(MaoJogador* mao){
    _mao = mao;
}

void Jogador::imprimir_mao() {
    int i = 0;
    for(Carta* c : _mao->get_cartas()) {
        std::cout << i << " - ";
        c->imprime_carta();
        i++;
    }
}

Carta* Jogador::jogar_carta(unsigned int indice) {
    return _mao->jogar_carta_selecionada(indice);
}

bool Jogador::verificar_vitoria(){
    return (_mao->get_numero_de_cartas() == 0);
}

int Jogador::get_id(){
    return _id;
}

MaoJogador* Jogador::get_mao(){
    return _mao;
}




