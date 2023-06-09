#include <iostream>
#include "../../include/jogador/jogador.hpp"

Jogador::Jogador(unsigned int id){
    _mao = new MaoJogador();
    _id = id;
}

Jogador::Jogador(){
    _numero_de_cartas_na_mao = 7;
}

Jogador::~Jogador(){
    delete _mao;
}

void Jogador::receber_cartas(MaoJogador* mao){
    delete _mao;
    _mao = mao;
}

void Jogador::imprimir_mao() {
    _mao->imprimir_baralho();
}

bool Jogador::is_bot(){
    return false;
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

    if((_mao->get_carta(indice)->get_cor() != curinga) && (_mao->get_carta(indice)->get_cor() != cor(4))) {
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

cor Jogador::get_cor_carta_mao(){
    for(int carta = 0; carta < _mao->get_numero_de_cartas();carta++){
        if(_mao->get_carta(carta)->get_cor() != cor(4)){
            return _mao->get_carta(carta)->get_cor();
        }
    }
    return cor(0);
}

void Jogador::set_pedir_uno(bool uno){
    _pediu_uno = uno;
}

bool Jogador::is_pediu_uno(){
    return _pediu_uno;
}



