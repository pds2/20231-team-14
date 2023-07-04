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
    _mao->imprimir_baralho();
}

Carta* Jogador::jogar_carta(unsigned int indice, Carta* carta_topo) {
    if(indice < 0 || indice >= _mao->get_numero_de_cartas()) {
        throw JogadaInvalida_e();
    }

    if(_mao->get_carta(indice)->get_cor() < cor(4)) {
        if(_mao->get_carta(indice)->get_cor() != carta_topo->get_cor() 
            && _mao->get_carta(indice)->get_valor() != carta_topo->get_valor()) {
                throw JogadaInvalida_e();
            }
    }
    return _mao->jogar_carta_selecionada(indice);

}

Carta* Jogador::jogar_carta_apenas_pela_cor(unsigned int indice, cor curinga) {
    if(indice < 0 || indice >= _mao->get_numero_de_cartas()) {
        throw JogadaInvalida_e();
    }

    if(_mao->get_carta(indice)->get_cor() != curinga) {
        throw JogadaInvalida_e();
    }
    
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




