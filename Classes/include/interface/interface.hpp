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
    /**
     * @brief Cria a layer para permitir a inserção de imagens na tela
    */
    static cocos2d::Scene* createScene();

    /*
    * @brief O jogo em si. Gerencia a ordem dos jogadores, jogadas de cartas e verifica se alguem venceu a partida
    */
    void criaPartida();

    /**
     * @brief Cria o sprite do baralho
    */
    void criaBaralho();

    /**
     * @brief Cria o sprite dos jogadores
    */
    void criaJogador();

    /**
     * @brief Cria o sprite do monte de cartas jogadas
    */
    void criaMonte(); 

    /**
     * @brief Inicializa a posição que cada jogador vai ocupar na tela
    */
    void inicializa_posicao_jogador(int index);

    /**
     * @brief Adiciona uma carta a mão de um jogador
    */
    void adicionarCarta(int posicao_carta, Jogador* jogador);

    /**
     * @brief Joga a carta da mão de um jogador
    */
    void jogarCarta(Carta *carta_clicada);

    /**
     * @brief Cria o evento de clicar e jogar as cartas da mão
    */
    void criar_jogar_carta_interface(int posicao_carta, Jogador* jogador);

    /**
     * @brief Cria o evento de clicar no baralho e comprar uma carta
    */
    void evento_comprar_carta_interface();

    /**
     * @brief Aplica os efeitos das cartas especiais do jogo
    */
    void aplicaCartaEspecial();

    /**
     * Cria a interface para o jogador seleciona a cor do coringa
    */
    void criar_interface_cor();

    /**
     * @brief Modifica a carta jogando ela em cima de um coringa ou uma carta comum
    */
    void modifica_carta(int posicao_carta_mao, MaoJogador *_mao);

    /**
     * @brief Função principal do jogo responsável pelo ciclo
    */
    virtual bool init(); 

    CREATE_FUNC(Interface);
    
private:
    bool _partida_finalizada;
    bool curinga;
    bool escolhendo_cor;
    cor cor_atual;
    int qntd_jogadores;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::SpriteFrameCache* spritescartas;
    Ciclo c;
    MonteCartasJogadas monte_principal;
    MonteCartasComer monte_compras;
    cocos2d::EventListenerTouchOneByOne* touchMonteComer;
    std::vector<cocos2d::Sprite*> quadrados_cor;
    std::vector <cocos2d::EventListenerTouchOneByOne*> touchCores;

};

#endif