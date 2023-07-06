#include "../../include/baralho/monteCartasComer.hpp"

MonteCartasComer::MonteCartasComer(unsigned int numero_cartas_iniciais, int qtd_jogadores, 
                                    std::vector<Carta*> cartas_restantes) : Baralho(
                                    108-(numero_cartas_iniciais*qtd_jogadores)-1, cartas_restantes) {};

MonteCartasComer::MonteCartasComer() : Baralho() {};

bool MonteCartasComer::checar_reinicio() {
    if(get_numero_de_cartas()==0) {
        return true;
    }
    return false;
}

void MonteCartasComer::reiniciar_monte(std::vector<Carta*> cartas_restantes) {
    alterar_cartas(cartas_restantes);
    alterar_numero_cartas(cartas_restantes.size());
    embaralhar_cartas();
}

Carta* MonteCartasComer::comer_carta() {
    if(get_numero_de_cartas()==0) {
        throw NumeroCartasInsuficientes_e();
    }

    std::vector<Carta*> vetor_temporario = get_cartas();
    int tam = vetor_temporario.size();
    Carta* ultima  = vetor_temporario[tam-1];
    vetor_temporario.pop_back();
    alterar_cartas(vetor_temporario);
    alterar_numero_cartas(vetor_temporario.size());
    return ultima;
}

void MonteCartasComer::criar_interface_monte_comer(cocos2d::Size visibleSize, cocos2d::Vec2 origin){
    cartasComerSprite = cocos2d::Sprite::create("BaralhoUno.png");
    cartasComerSprite->setContentSize(cocos2d::Size(visibleSize.height/7, visibleSize.width/7));
    cartasComerSprite->setAnchorPoint(cocos2d::Vec2(0, 0));
    float x = origin.x;
    float y = origin.y + visibleSize.height - cartasComerSprite->getContentSize().height;
    cartasComerSprite->setPosition(x, y);
}

cocos2d::Sprite* MonteCartasComer::get_interface_monte_comer(){
    return cartasComerSprite;
}