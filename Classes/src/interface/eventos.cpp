#include "../../include/interface/eventos.hpp"

void Eventos::cria_eventos_jogar_carta(int qntd_jogadores){
    for(int jogador = 0; jogador < qntd_jogadores; jogador++){
        std::vector<cocos2d::EventListenerTouchOneByOne*> eventos_clique_cartas;
        touchCartas.push_back(eventos_clique_cartas);
    }
}

void Eventos::adicionar_evento_jogar_carta(cocos2d::EventListenerTouchOneByOne* touchCarta, int jogador){
    touchCartas.at(jogador).push_back(touchCarta);
}

void Eventos::remover_evento_jogar_carta(int posicao_carta, int jogador){
    touchCartas.at(jogador).erase(touchCartas.at(jogador).begin() + posicao_carta);
}

cocos2d::EventListenerTouchOneByOne* Eventos::get_evento_jogar_carta(int indice, int jogador){
    return touchCartas.at(jogador).at(indice);
}

void Eventos::adicionar_evento_comprar_carta(cocos2d::EventListenerTouchOneByOne* touchBaralho){
    touch_baralho = touchBaralho;
}

cocos2d::EventListenerTouchOneByOne* Eventos::get_evento_comprar_carta(){
    return touch_baralho;
}

void Eventos::adicionar_evento_escolha_cor(cocos2d::EventListenerTouchOneByOne* touchCor){
    touch_cores.push_back(touchCor);
}

cocos2d::EventListenerTouchOneByOne* Eventos::get_evento_escolha_cor(int indice){
    return touch_cores.at(indice);
}

void Eventos::clear_evento_escolha_cor(){
    touch_cores.clear();
}