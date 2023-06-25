#ifndef SPRITE_BARALHO_HPP
#define SPRITE_BARALHO_HPP

#include "cocos2d.h"
#include "../../include/cartas/cartas.hpp"
#include <iostream>
#include <list>
#include <vector>

class SpriteBaralho : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    void criaBaralho();
    void criaBot(int botID);
    void adicionarBotTela(double posicao_bot_x, double posicao_bot_y, bool variando_x, int quantidade_cartas, int rotacao,int botID);
    void jogarCartaBot(int botID, Carta carta_jogada, double posicao_bot_x, double posicao_bot_y, bool variando_x);
    void criaJogador();
    void criaMonte();
    void eventoCliqueCarta(Carta carta_clicada);
    void adicionarCarta(Carta maoCarta, int posicao_carta);
    void organizarMaoJogador();
    virtual bool init();  
    CREATE_FUNC(SpriteBaralho);
private:
    std::vector<int> quantidade_cartas;
    int tamanhoCarta;
    int larguraCarta;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Sprite* baralho;
    cocos2d::EventListenerTouchOneByOne* touchListener;
    cocos2d::SpriteFrameCache* spritescartas;
    cocos2d::Sprite* carta_jogada;
    std::list<Carta> maoJogador;
    std::list<cocos2d::Sprite*> cartas_mao;
    std::list<cocos2d::EventListenerTouchOneByOne*> touchCartas;

    std::list<cocos2d::Sprite*> cartas_bot0;
    std::list<cocos2d::Sprite*> cartas_bot1;
    std::list<cocos2d::Sprite*> cartas_bot2;
};

#endif