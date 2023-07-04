#include "../../include/baralho/monteCartasJogadas.hpp"

MonteCartasJogadas::MonteCartasJogadas(std::vector<Carta*> carta_inicial) : Baralho(1,carta_inicial) {};

MonteCartasJogadas::MonteCartasJogadas() : Baralho() {};

Carta* MonteCartasJogadas::mostrar_topo() {
    std::vector<Carta*> vetor_temporario = get_cartas();
    return vetor_temporario[vetor_temporario.size()-1];
}

void MonteCartasJogadas::adicionar_carta_topo(Carta* carta_jogada) {
    std::vector<Carta*> vetor_temporario = get_cartas();
    vetor_temporario.push_back(carta_jogada);
    alterar_cartas(vetor_temporario);
}

void MonteCartasJogadas::criar_inteface_monte_jogadas(cocos2d::Size visibleSize, cocos2d::Vec2 origin){
    carta_jogada = cocos2d::Sprite::createWithSpriteFrameName((*mostrar_topo()).get_sprite());
    carta_jogada->setAnchorPoint(cocos2d::Vec2(0, 0));
    carta_jogada->setContentSize(cocos2d::Size(visibleSize.height/11, visibleSize.width/11));
    carta_jogada->setPosition(origin.x + (visibleSize.width/2) - (carta_jogada->getContentSize().width/2) , origin.y + (visibleSize.height/2) - (carta_jogada->getContentSize().height/2));
}

cocos2d::Sprite* MonteCartasJogadas::get_inteface_monte_jogadas(){
    return carta_jogada;
}

void MonteCartasJogadas::set_inteface_monte_jogadas(cocos2d::Sprite* sprite){
    carta_jogada = sprite;
}