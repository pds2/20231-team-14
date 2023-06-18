#ifndef SPRITE_BARALHO_HPP
#define SPRITE_BARALHO_HPP

#include "cocos2d.h"
#include "../../include/cartas/cartas.hpp"
#include <iostream>
#include <list>

class SpriteBaralho : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    void criaBaralho();
    void criaBot();
    void criaJogador();
    void criaMonte();
    void adicionarCarta(Carta maoCarta, int posicao_carta);
    virtual bool init();  
    CREATE_FUNC(SpriteBaralho);
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Sprite* baralho;
    cocos2d::EventListenerTouchOneByOne* touchListener;
    cocos2d::SpriteFrameCache* spritescartas;
    cocos2d::Sprite* carta_jogada;
    std::list<Carta> maoJogador;
    std::list<cocos2d::Sprite*> cartas_mao;
    std::list<cocos2d::EventListenerTouchOneByOne*> touchCartas;
};

#endif