#ifndef SPRITES_HPP
#define SPRITES_HPP

#include "cocos2d.h"
#include "../../include/cartas/cartas.hpp"
#include <vector>
#include <string>

class Sprites{  
    private:
        cocos2d::SpriteFrameCache* spritescartas;
        cocos2d::SpriteFrameCache* spritescartaspretas;
        std::vector<std::vector<cocos2d::Sprite*>> cartas_mao;
        cocos2d::Sprite* cartasComerSprite;
        cocos2d::Sprite* carta_jogada;
        std::vector<cocos2d::Sprite*> escolha_cores;
        cocos2d::Sprite* simbolo_uno;
        cocos2d::Size visibleSize;
        cocos2d::Vec2 origin;
        std::vector<int> rotacao;
        std::vector<double> posicao_x,  posicao_y;
        std::vector<bool> variacao_x, bot;
        cocos2d::Size tamanho;
    public:

        /**
         * @brief Inicializa as dimensões de tela
        */
        Sprites();

        /**
         * @brief Retorna o sprite da carta
         * @param carta A carta desejada
         */
        std::string get_sprite(Carta* carta);

        /**
         * @brief Retorna se o jogador é um bot
         * @param jogador Jogador a ser identificado
         * @return Retorna se a mão é de um bot
        */
        bool is_bot(int jogador);

        /**
         * @brief Inicializa posição das cartas na tela
         * @param qntd_jogadores Quantidade de jogadores na partida
        */
        void inicializa_posicao_cartas(int qntd_jogadores);

        /**
         * @brief Cria o sprite da carta do jogador para imprimi-lo na tela
         * @param posicao_carta Posicao da carta na mão
         * @param jogador Indice do jogador
         * @param carta A carta que será adicionada
         * @param numero_cartas Quantidade de cartas do jogador ou bot
        */
        void criar_interface_carta_mao(int posicao_carta, int jogador, Carta* carta, int numero_cartas);

        /**
         * @brief Retorna o sprite da carta do jogador para imprimi-lo na tela
         * @param indice Indice da carta
         * @param jogador Indice do jogador
         * @return Retorna o sprite da carta da mão do jogador
        */
        cocos2d::Sprite* get_interface_carta_mao(int indice, int jogador);      

        /**
         * @brief Mostra a carta jogada pelo bot
         * @param posicao_carta Posicao da carta na mão do jogador
         * @param jogador Indice do jogador
         * @param carta A carta do bot que será mostrada
        */
        void mostra_carta_bot(int posicao_carta, int jogador, Carta* carta);

        /**
         * @brief Move a carta selecionada pelo jogador para o centro da mesa
         * @param posicao_carta_mao Indice da carta da mão do jogador
         * @param jogador Indice do jogador
        */
        void mover_carta_centro(int posicao_carta_mao, int jogador);

        /**
         * @brief Retorna o sprite do monte para imprimi-lo na tela 
         * @return Sprite do baralho do jogador
        */
        cocos2d::Sprite* get_interface_monte_comer();      

        /**
         * @brief Criar o sprite do baralho
        */
        void criar_interface_monte_comer();

        /**
         * @brief Cria o sprite da carta no topo para mostra-lo na tela
         * @param carta_inicio
        */
        void criar_inteface_monte_jogadas(Carta* carta_inicio);

        /**
         * @brief Retorna o sprite da carta no topo para mostra-lo na tela
         * @return 
        */
        cocos2d::Sprite* get_inteface_monte_jogadas();

        /**
         * @brief Organiza a mão do jogador na tela
         * @param jogador Indice do jogador
         * @param numero_de_cartas Quantidade de cartas
        */
        void organizar_mao_jogador(int jogador, int numero_de_cartas);

        /**
         * @brief Cria a sprite de escolha de cores
        */
        void cria_interface_escolha_cor(std::string cor, int quadrados);

        /**
         * @brief Muda a cor da carta jogada para a cor escolhida pelo jogador
        */
        void muda_cor_curinga(Carta* carta, cor cor_escolihida);

        /**
         * @brief Retorna a interface de escolha de cor
        */
        cocos2d::Sprite* get_interface_escolha_cor(int indice);

        /**
         * @brief Limpa os escolhas de cor
        */
        void clear_interface_escolha_cor();

        /**
         * @brief Cria a interface de gritar Uno
        */
        void cria_interface_gritar_Uno();

        /**
         * @brief Retorna a interfade de gritar uno
        */
        cocos2d::Sprite* get_interface_gritar_Uno();
        
};

#endif