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

class PartidaInvalida_e {};

class Interface : public cocos2d::Layer{
public:
    /**
     * @brief Cria a layer para permitir a inserção de imagens na tela
    */
    static cocos2d::Scene* createScene();

    /**
     * @brief Função principal do jogo responsável pelo ciclo
    */
    virtual bool init(); 

    /*
    * @brief O jogo em si. Gerencia a ordem dos jogadores, jogadas de cartas e verifica se alguem venceu a partida
      @throws Lança uma exceção caso a quantidade de jogadores seja negativa/maior do que 9 ou o número de cartas seja insuficiente
    */
    void cria_partida();

    /**
     * @brief Cria o sprite do baralho
    */
    void cria_baralho();

    /**
     * @brief Cria o sprite dos jogadores
    */
    void cria_jogador(int jogador);

    /**
     * @brief Cria o sprite do monte de cartas jogadas
    */
    void cria_monte(); 

  /**
   * @brief Seta a carta coringa
  */
    void setar_curinga();

    /*
     * @brief Prepara um monte já embaralhado para começar a partida 
    */
    MonteCartasIniciais* preparar_monte_inicial();

    /*
     * @brief Prepara o monte de cartas que será usado para compras
    */
    void preparar_monte_cartas_para_compra(MonteCartasIniciais* monte_inicial);

    /*
     * @brief Prepara o monte de cartas que serão jogadas
    */
    void preparar_monte_cartas_jogadas(MonteCartasIniciais* monte_inicial); 

    /*
     * @brief Prepara os jogadores da partida
    */
    void preparar_jogadores(MonteCartasIniciais* monte_inicial);

    /*
     * @brief Faz a jogada da vez
    */
    void fazer_jogada(int indice_carta,MaoJogador *_mao);

    /*
     * @brief Checa e reincia, se necessário, o monte de compras
    */
    void checar_reinicio_monte_compras();

    /*
     * @brief Aplica um efeito especial se necessário
    */
    void aplicar_efeito_especial();

    /**
     * @brief Aplica a compra de uma carta para o próximo jogador
    */
    void aplicar_compra_proximo_jogador();

    /*
     * @brief Aplica a mudança de cor do baralho se necessário
    */
    void aplicar_mudanca_cor();

    /**
     * @brief Inicializa a posição que cada jogador vai ocupar na tela
    */
    void inicializa_posicao_jogador(int index);

    /**
     * @brief Adiciona uma carta a mão de um jogador
    */
    void adicionar_carta(int posicao_carta, Jogador* jogador);

    /**
     * @brief Joga a carta da mão de um jogador
    */
    void jogar_carta(Carta *carta_clicada);

    /**
     * @brief Cria o evento de clicar e jogar as cartas da mão
    */
    void jogar_carta_clique(int posicao_carta, Jogador* jogador);

    /*
     * @brief Cria o evento de comprar uma carta quando clicar no baralho
    */
    void comprar_carta();

    /**
     * Cria a interface para o jogador seleciona a cor do coringa
    */
    void criar_interface_cor();

    /**
     * @brief Modifica a carta jogando ela em cima de um coringa ou uma carta comum
    */
    void mandar_carta(int posicao_carta_mao, MaoJogador *_mao);

    CREATE_FUNC(Interface);
    
private:
    bool _partida_finalizada;
    bool curinga;
    bool escolhendo_cor;
    cor cor_atual;
    int qntd_jogadores;
    int qntd_cartas_iniciais;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::SpriteFrameCache* spritescartas;
    Ciclo *c;
    MonteCartasJogadas *monte_principal;
    MonteCartasComer *monte_compras;
    cocos2d::EventListenerTouchOneByOne* touchMonteComer;
    std::vector<cocos2d::Sprite*> quadrados_cor;
    std::vector <cocos2d::EventListenerTouchOneByOne*> touchCores;

};

#endif