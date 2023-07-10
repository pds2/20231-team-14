#include "../include/ciclo.hpp"

#include <algorithm>

Ciclo::Ciclo(){
    _indexJogador = 0;
}

Ciclo::~Ciclo() {
    for(Jogador* j : _jogadores) {
        delete j;
    }
}

void Ciclo::adicionar_jogadores(Jogador* j){
    _jogadores.push_back(j);
}

void Ciclo::proximo_jogador(){
    _indexJogador++;
    if(_indexJogador >= _jogadores.size()) _indexJogador = 0;
}

Jogador* Ciclo::get_jogador_atual(){
    return _jogadores[_indexJogador];
}

void Ciclo::inverter(){
    Jogador* atual = get_jogador_atual();
    std::reverse(_jogadores.begin(), _jogadores.end());

    _indexJogador = 0;
    for(Jogador* j : _jogadores){
        if(j == atual) break;
        _indexJogador++;
    }
}

Jogador* Ciclo::get_proximo_jogador() {
    if((_indexJogador+1) > (int)_jogadores.size()) {
        return _jogadores[0];
    }
    return _jogadores[_indexJogador+1];
}

short Ciclo::get_index(){
    return _indexJogador;
}

Jogador* Ciclo::get_jogador(int i){
    for(Jogador* j : _jogadores){
        if(j->get_id() == i) return j;
    }
}

Jogador* Ciclo::get_jogador_por_indice(int indice) {
    if(indice < 0 || indice >= (int)_jogadores.size()) {
        throw IndiceJogadorInvalido_e();
    }
    return _jogadores[indice];
}
