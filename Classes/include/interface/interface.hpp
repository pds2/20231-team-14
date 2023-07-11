#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "cocos2d.h"
#include "../sistema/sistema.hpp"
#include "eventos.hpp"
#include "sprites.hpp"
#include <iostream>

class Interface : public cocos2d::Layer{
private:
    bool escolhendo_cor;
    int posicao_carta_bot;
    bool apareceu_pedir_uno;
    Sistema *sistema;
    Eventos eventos;
    Sprites sprites;

public:
    /**
     * @brief Cria a layer para permitir a inserção de imagens na tela
     * @return Toda a cena do programa que sera exibida na tela
    */
    static cocos2d::Scene* createScene();

    /**
     * @brief Função principal do jogo responsável pelo ciclo
     * @return Retorna true ou false
    */
    virtual bool init(); 

    /**
     * @brief Realiza as ações de jogar carta do bot
    */
    void jogar_carta_bot(float dt);

    /**
     * @brief Inicializa a jogada de cartas do bot
    */
    void inicializa_jogar_carta_bot(float dt);

    /**
     * @brief Destroi o sistema após o fime do programa
    */
    ~Interface();

    /**
     * @brief Cria o sprite do baralho
    */
    void cria_baralho();

    /**
     * @brief Cria o sprite dos jogadores
     * @param jogador ID do jogador que será criado
    */
    void cria_jogador(int jogador);

    /**
     * @brief Cria o sprite do monte de cartas jogadas
    */
    void cria_monte(); 

    /**
     * @brief Inicializa a posição que cada jogador vai ocupar na tela
     * @param index ID do jogador que será posicionado
    */
    void inicializa_posicao_jogador(int index);

    /**
     * @brief Adiciona o sprite de uma carta na mão de um jogador
     * @param posicao_carta Posição da carta na mão do jogador
     * @param jogador Jogador que terá ua carta adicionada na sua mão
    */
    void adicionar_carta(int posicao_carta, Jogador* jogador);

    /**
     * @brief Cria o evento de comprar uma carta quando clicar no baralho
    */
    void comprar_carta_clique();

    /**
     * @brief Organiza os procedimentos para comprar uma carta
    */
    void organiza_compra_carta();

    /**
     * @brief Cria o evento de clicar e jogar as cartas da mão
     * @param posicao_carta Posição da carta na mão do jogador
     * @param jogador Jogador que terá o evento da carta adicionado em uma carta da sua mão
    */
    void jogar_carta_clique(int posicao_carta, Jogador* jogador);
    /**
     * @brief Organiza os procedimentos após jogar uma carta
     * @param carta Carta que foi jogada pelo jogador
     * @param jogadorID ID do jogador que jogou a carta
    */
    void organizar_jogada(Carta* carta, int jogadorID);

    /**
     * @brief Movimenta a carta clicada da mão do jogador até o centro
     * @param posicao_carta_mao Posição da carta na mão do jogador
    */
    void jogar_sprite_carta(int posicao_carta_mao);

    /**
     * @brief Cria a interface para o jogador selecionar a cor do coringa
    */
    void criar_interface_cor();

    /**
     * @brief Cria a interface para o jogador gritar uno
    */
    void cria_interface_uno();

    /**
     * @brief Função que cria a Interface
    */
    CREATE_FUNC(Interface);


};

#endif