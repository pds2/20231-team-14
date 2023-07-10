#ifndef SPRITES_HPP
#define SPRITES_HPP

#include "cocos2d.h"
#include "../../include/cartas/cartas.hpp"
#include <vector>
#include <string>

class Sprites{
    public:

        /**
         * @brief Inicializa as dimensões de tela
        */
        Sprites();

        /*
         * @brief Retorna o sprite da carta
         */
        std::string get_sprite(Carta* carta);

        /**
         * @brief Retorna se o jogador é um bot
        */
        bool is_bot(int jogador);

        /**
         * @brief Inicializa posição das cartas mdos jogadores
        */
        void inicializa_posicao_cartas(int qntd_jogadores);

        /**
         * @brief Cria o sprite da carta do jogador para imprimi-lo na tela
        */
        void criar_interface_carta_mao(int posicao_carta, int jogador, Carta* carta, int numero_cartas);

        /**
         * @brief Retorna o sprite da carta do jogador para imprimi-lo na tela
        */
        cocos2d::Sprite* get_interface_carta_mao(int indice, int jogador);      

        /**
         * @brief Mostra a carta jogada pelo bot
        */
        void mostra_carta_bot(int posicao_carta, int jogador, Carta* carta);

        /**
         * @brief Move a carta selecionada pelo jogador para o centro da mesa
        */
        void mover_carta_centro(int posicao_carta_mao, int jogador);

        /*
         * @brief Retorna o sprite do monte para imprimi-lo na tela 
        */
        cocos2d::Sprite* get_interface_monte_comer();      

        /*
         * @brief Criar o sprite do baralho
        */
        void criar_interface_monte_comer();

        /**
         * @brief Cria o sprite da carta no topo para mostra-lo na tela
        */
        void criar_inteface_monte_jogadas(Carta* carta_inicio);

        /**
         * @brief Retorna o sprite da carta no topo para mostra-lo na tela
        */
        cocos2d::Sprite* get_inteface_monte_jogadas();

        /**
         * @brief Organiza a mão do jogador na tela
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
        
    private:
        cocos2d::SpriteFrameCache* spritescartas;
        cocos2d::SpriteFrameCache* spritescartaspretas;
        std::vector<std::vector<cocos2d::Sprite*>> cartas_mao;
        cocos2d::Sprite* cartasComerSprite;
        cocos2d::Sprite* carta_jogada;
        std::vector<cocos2d::Sprite*> escolha_cores;
        cocos2d::Size visibleSize;
        cocos2d::Vec2 origin;
        std::vector<int> rotacao;
        std::vector<double> posicao_x,  posicao_y;
        std::vector<bool> variacao_x, bot;
        cocos2d::Size tamanho;
};

#endif