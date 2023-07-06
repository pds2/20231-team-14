#include "../../include/baralho/maoJogador.hpp"
#include <iostream>
#include <string>

MaoJogador::MaoJogador(unsigned int qtd_cartas_inicial, 
                       std::vector<Carta*> mao_inicial) : Baralho(qtd_cartas_inicial, mao_inicial) {};

MaoJogador::MaoJogador(): Baralho() {}

Carta* MaoJogador::jogar_carta_selecionada(unsigned int indice) {
    if(indice >= get_numero_de_cartas()) {
        throw IndiceInvalido_e();
    }
    
    std::vector<Carta*> vetor_temporario = get_cartas();
    Carta* jogada_da_vez = vetor_temporario[indice];
    vetor_temporario.erase(vetor_temporario.begin()+indice);
    alterar_cartas(vetor_temporario);
    return jogada_da_vez;
}

void MaoJogador::comprar_carta(Carta* carta_comprada) {
    std::vector<Carta*> vetor_temporario = get_cartas();
    vetor_temporario.push_back(carta_comprada);
    alterar_cartas(vetor_temporario);
}

void MaoJogador::criar_interface_carta_mao(int posicao_carta,double posicao_x, double posicao_y, bool variando_x, int rotacao, cocos2d::Size tamanho, bool bot){
    cocos2d::Sprite* carta_mao;
    if(bot) carta_mao = cocos2d::Sprite::createWithSpriteFrameName("card_back.png");
    else carta_mao = cocos2d::Sprite::createWithSpriteFrameName(get_carta(posicao_carta)->get_sprite());
    carta_mao->setAnchorPoint(cocos2d::Vec2(0, 0));
    carta_mao->setContentSize(tamanho);
    if(variando_x) carta_mao->setPosition(posicao_x + posicao_carta * carta_mao->getContentSize().width, posicao_y);
    else carta_mao->setPosition(posicao_x, posicao_y + posicao_carta * carta_mao->getContentSize().width);
    
    carta_mao->runAction(cocos2d::RotateTo::create(0,rotacao));
    cartas_mao.push_back(carta_mao);
}

cocos2d::Sprite* MaoJogador::get_interface_carta_mao(int indice){
    return cartas_mao.at(indice); 
}

void MaoJogador::remove_interface_carta_mao(int indice){
    cartas_mao.erase (cartas_mao.begin() + indice);
}


