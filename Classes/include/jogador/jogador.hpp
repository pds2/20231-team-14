#ifndef UNO_JOGADOR_HPP
#define UNO_JOGADOR_HPP

#include "../baralho/baralho.hpp"
#include "../baralho/maoJogador.hpp"
#include "../baralho/monteCartasJogadas.hpp"
#include "../baralho/monteCartasComer.hpp"
#include "cocos2d.h"

class JogadaInvalida_e {};
class Jogador {
    private:
        unsigned int _numero_de_cartas_na_mao;
        MaoJogador* _mao;
        unsigned int _id; //apenas para testes da classe "ciclo"
        std::vector<cocos2d::EventListenerTouchOneByOne*> touchCartas;
        int rotacao;
        double posicao_x,  posicao_y;
        bool variacao_x, bot;
        cocos2d::Size tamanho;
    public:
        /*
         * @brief Constrói um jogador com 7 cartas em mãos
         */
        Jogador(unsigned int id);

        /**
         * @brief Construi um jogador vazio
        */
        Jogador();

        /**
         * @brief Destroi a mão do jogador
        */
        ~Jogador();

        /**
         * @brief Inicializa a posição do jogador na Interface
        */
        void inicializa_posicao_cartas(double posicao_x, double posicao_y, bool variando_x, int rotacao, cocos2d::Size tamanho, bool bot);

        /*
         * @brief Recebe cartas
        */
        void receber_cartas(MaoJogador*);
        
        /*
         * @brief Imprime a mão de um jogador
         */
        void imprimir_mao();

        /**
         * @brief Joga a carta especificada pelo índice, caso a jogada seja válida
         * @throws Lança uma exceção caso a carta selecionada não possa ser jogada
         */
        Carta* jogar_carta(unsigned int indice, Carta* carta_topo);

        /**
         * @brief Verifica se a jogada é possível com a carta
        */
        bool verifica_carta_jogada(unsigned int indice, Carta* carta_topo);

        /**
         * @brief Verifica se a jogada é possível com a cor
        */
        bool verifica_cor_jogada(unsigned int indice, cor curinga);

        /*
         * @brief Joga a carta especificada pelo índice, caso a jogada seja válida (analisando somente a cor do coringa)
         * @throws Lança uma exceção caso a carta selecionada não possa ser jogada
         */
        Carta* jogar_carta_apenas_pela_cor(unsigned int indice, cor curinga);

        /*
        * @brief Vence o jogo quando chegar a 0 cartas.
        */
        bool verificar_vitoria();

        /*
        * @brief Retorna id.
        */
        int get_id();

        /*
         * @brief Retorna a mão do jogador.
        */
        MaoJogador* get_mao();

        /**
         * @brief Cria a mão do jogador
        */
        void criar_interface_mao(int posicao_carta);

        /**
         * @brief Retorna o sprite da mão 
        */
        cocos2d::Sprite* get_sprite_mao(int indice);

        /**
         * @brief Organiza a mão do jogador na tela
        */
        void organizar_mao_jogador();

        /**
         * @brief Adiciona o evento de clicar em uma carta
        */
        void adicionar_evento(cocos2d::EventListenerTouchOneByOne* touchCarta);

        /**
         * @brief Remove o evento de clicar em uma carta
        */
        void remover_evento(int posicao_carta);

        /**
         * @brief Retorna o evento de clicar em uma carta
        */
        cocos2d::EventListenerTouchOneByOne* get_evento(int indice);
       
};

#endif