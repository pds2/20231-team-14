#ifndef UNO_MAO_JOGADOR_HPP
#define UNO_MAO_JOGADOR_HPP

#include "baralho.hpp"
#include "cocos2d.h"

class MaoJogador : public Baralho {
    private:
        std::vector<cocos2d::Sprite*> cartas_mao;
    public:
        /*
         * @brief Constrói a mão do início de cada partida
        */
        MaoJogador(unsigned int qtd_cartas_inicial, std::vector<Carta*> mao_inicial);

        /**
         * @brief Constói a mão de jogador vazia
        */
        MaoJogador();

        /*
         * @brief Retira da mão a carta com o índice especificado
        */
        Carta* jogar_carta_selecionada(unsigned int indice);

        /*
         * @brief Adiciona na mão a carta comprada pelo jogador
        */
        void comprar_carta(Carta* carta_comprada);

        /**
         * @brief Cria o sprite da carta do jogador para imprimi-lo na tela
        */
        void criar_interface_carta_mao(int posicao_carta,double posicao_x, double posicao_y, bool variando_x, int rotacao, cocos2d::Size tamanho, bool bot);

        /**
         * @brief Retorna o sprite da carta do jogador para imprimi-lo na tela
        */
        cocos2d::Sprite* get_interface_carta_mao(int indice);      

        /**
         * @brief Remove o sprite da carta jogada da mão
        */
        void remove_interface_carta_mao(int indice);
};

#endif