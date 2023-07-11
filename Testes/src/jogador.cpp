#include <iostream>
#include "../include/jogador.hpp"

Jogador::Jogador(unsigned int id){
    set_mao();
    set_id(id);
    set_humano(true);
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

Carta* Jogador::jogar_carta(unsigned int indice, Carta* carta_topo) {
    if(!verifica_carta_jogada(indice, carta_topo)) {
        throw JogadaInvalida_e();
        std::cout << "\nTente outra carta\n";
    }
    return _mao->jogar_carta_selecionada(indice);
}

bool Jogador::verifica_carta_jogada(unsigned int indice, Carta* carta_topo){
    if(indice < 0 || indice >= _mao->get_numero_de_cartas()) {
        return false;
    }
    if(carta_topo->get_cor() == cor(4)) return true;
    if(_mao->get_carta(indice)->get_cor() < cor(4)) {
        if(_mao->get_carta(indice)->get_cor() != carta_topo->get_cor() && _mao->get_carta(indice)->get_valor() != carta_topo->get_valor()) {
                return false;
            }
    }
    
    return true;
}

bool Jogador::verifica_cor_jogada(unsigned int indice, cor curinga){
    if(indice < 0 || indice >= _mao->get_numero_de_cartas()) {
        return false;
    }

    if((_mao->get_carta(indice)->get_cor() != curinga) && (_mao->get_carta(indice)->get_cor() != cor(4))) {
        return false;
    }  
    return true;
}

Carta* Jogador::jogar_carta_apenas_pela_cor(unsigned int indice, cor curinga) {
    if(!verifica_cor_jogada(indice,curinga)) throw JogadaInvalida_e();
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

bool Jogador::get_humano(){
    return _humano;
}

void Jogador::set_humano(bool b){
    _humano = b;
}

void Jogador::set_id(unsigned int id){
    _id = id;
}

void Jogador::set_mao(){
    _mao = new MaoJogador();
}

void Jogador::set_pedir_uno(bool uno){
    _pediu_uno = uno;
}

bool Jogador::get_pediu_uno(){
    return _pediu_uno;
}

