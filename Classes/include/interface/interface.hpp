#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "cocos2d.h"
#include "../../include/cartas/cartas.hpp"
#include "../../include/baralho/monteCartasComer.hpp"
#include "../../include/baralho/monteCartasIniciais.hpp"
#include "../../include/baralho/monteCartasJogadas.hpp"
#include "../../include/baralho/maoJogador.hpp"
#include "../../include/jogador/jogador.hpp"
#include "../../include/jogador/bot.hpp"
#include "ciclo.hpp"
#include <iostream>
#include <vector>

class Interface : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    void criaBaralho();
    void criaJogador();
    void criaMonte(); 
    /*
    * @brief Seta "_partida_finalizada" = true.
    */
    void finalizarPartida();

    /*
    * @brief O jogo em si. Gerencia a ordem dos jogadores, jogadas de cartas e verifica se alguem venceu a partida
    */
    void criaPartida();
    void adicionarCarta(int posicao_carta, int jogador);
    void jogarCarta(Carta *carta_clicada, int jogador);
    void organizarMaoJogador();
    void criar_jogar_carta_interface(int posicao_carta, int jogador);
    void evento_comprar_carta_interface();

    virtual bool init(); 

    CREATE_FUNC(Interface);
    
private:
    bool _partida_finalizada;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::SpriteFrameCache* spritescartas;
    Ciclo c;
    MonteCartasJogadas monte_principal;
    MonteCartasComer monte_compras;
    std::vector<cocos2d::EventListenerTouchOneByOne*> touchCartas;
    cocos2d::EventListenerTouchOneByOne* touchMonteComer;

    
};

#endif