#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "cocos2d.h"
#include "../sistema/sistema.hpp"
#include "eventos.hpp"
#include "sprites.hpp"

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

    /**
     *@brief Destroi o sistema após o fime do programa
    */
    ~Interface();

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
     * @brief Inicializa a posição que cada jogador vai ocupar na tela
    */
    void inicializa_posicao_jogador(int index);

    /**
     * @brief Adiciona o sprite de uma carta na mão de um jogador
    */
    void adicionar_carta(int posicao_carta, Jogador* jogador);

    /**
     * @brief Cria o evento de comprar uma carta quando clicar no baralho
    */
    void comprar_carta_clique();

    /**
     * @brief Cria o evento de clicar e jogar as cartas da mão
    */
    void jogar_carta_clique(int posicao_carta, Jogador* jogador);

    /**
     * @brief Organiza os procedimentos após jogar uma carta
    */
    void organizar_jogada(Carta* carta, int jogadorID);

    /**
     * @brief Movimenta a carta clicada da mão do jogador até o centro
    */
    void jogar_sprite_carta(int posicao_carta_mao);

    /**
     * @brief Cria a interface para o jogador selecionar a cor do coringa
    */
    void criar_interface_cor();

    CREATE_FUNC(Interface);
private:
    bool escolhendo_cor;
    cocos2d::SpriteFrameCache* spritescartas;
    Sistema *sistema;
    Eventos eventos;
    Sprites sprites;

};

#endif