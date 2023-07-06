#include <iostream>
#include "../../include/jogador/jogador.hpp"

Jogador::Jogador(unsigned int id){
    _mao = new MaoJogador();
    _id = id;
}

Jogador::Jogador(){
    _numero_de_cartas_na_mao = 7;
    //_mao = mao;
}

Jogador::~Jogador(){
    delete _mao;
}

void Jogador::receber_cartas(MaoJogador* mao){
    _mao = mao;
}

void Jogador::imprimir_mao() {
    _mao->imprimir_baralho();
}

Carta* Jogador::jogar_carta(unsigned int indice, Carta* carta_topo) {
    if(!verifica_carta_jogada(indice, carta_topo)) throw JogadaInvalida_e();
    return _mao->jogar_carta_selecionada(indice);
}

bool Jogador::verifica_carta_jogada(unsigned int indice, Carta* carta_topo){
    if(indice < 0 || indice >= _mao->get_numero_de_cartas()) {
        return false;
    }

    if(_mao->get_carta(indice)->get_cor() < cor(4)) {
        if(_mao->get_carta(indice)->get_cor() != carta_topo->get_cor() 
            && _mao->get_carta(indice)->get_valor() != carta_topo->get_valor()) {
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

void Jogador::inicializa_posicao_cartas(double posicao_x, double posicao_y, bool variando_x, int rotacao, cocos2d::Size tamanho, bool bot){
    this->posicao_x = posicao_x;
    this->posicao_y = posicao_y;
    this->variacao_x = variando_x;
    this->rotacao = rotacao;
    this->tamanho = tamanho;
    this->bot = bot;   
}


void Jogador::criar_interface_mao(int posicao_carta){
    double posicao_x_temporaria = posicao_x;
    double posicao_y_temporaria = posicao_y;
    if(variacao_x) posicao_x_temporaria -= (_mao->get_numero_de_cartas() * tamanho.height)/3;
    else posicao_y_temporaria -=(_mao->get_numero_de_cartas() * tamanho.height)/3;
    _mao->criar_interface_carta_mao(posicao_carta,posicao_x_temporaria, posicao_y_temporaria, variacao_x, rotacao, tamanho, bot);
}

void Jogador::organizar_mao_jogador(){
    double posicao_x_temporaria = posicao_x;
    double posicao_y_temporaria = posicao_y;
    if(variacao_x) posicao_x_temporaria -= (_mao->get_numero_de_cartas() * tamanho.height)/3;
    else posicao_y_temporaria -=(_mao->get_numero_de_cartas() * tamanho.height)/3;

    for(int posicao_carta = 0; posicao_carta < _mao->get_numero_de_cartas(); posicao_carta++){
        if(variacao_x){
            _mao->get_interface_carta_mao(posicao_carta)->setPosition(posicao_x_temporaria + posicao_carta * _mao->get_interface_carta_mao(posicao_carta)->getContentSize().width, posicao_y_temporaria);
        }else {
            _mao->get_interface_carta_mao(posicao_carta)->setPosition(posicao_x_temporaria, posicao_y_temporaria + posicao_carta * _mao->get_interface_carta_mao(posicao_carta)->getContentSize().width);
        }
    }  
}

cocos2d::Sprite* Jogador::get_sprite_mao(int indice){
    cocos2d::Sprite* carta = _mao->get_interface_carta_mao(indice);
    return carta;
}

void Jogador::adicionar_evento(cocos2d::EventListenerTouchOneByOne* touchCarta){
    touchCartas.push_back(touchCarta);
}

void Jogador::remover_evento(int posicao_carta){
    touchCartas.erase(touchCartas.begin() + posicao_carta);
}

cocos2d::EventListenerTouchOneByOne* Jogador::get_evento(int indice){
    return touchCartas.at(indice);
}



