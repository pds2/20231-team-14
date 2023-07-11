#ifndef UNO_MAO_JOGADOR_HPP
#define UNO_MAO_JOGADOR_HPP

#include "baralho.hpp"

class MaoJogador : public Baralho {
    public:
        /**
         * @brief Constrói a mão do início de cada partida
         * @param qtd_cartas_inicial Quantidade de cartas na mao
         * @param mao_inicial As cartas da mao
        */
        MaoJogador(unsigned int qtd_cartas_inicial, std::vector<Carta*> mao_inicial);

        /**
         * @brief Constói a mão de jogador vazia
        */
        MaoJogador();

        /**
         * @brief Retira da mão a carta com o índice especificado
         * @param indice Posicao da carta na mao a ser retirada
         * @throws Lanca uma exceção caso não exista uma carta com o índice indicado
         * @return Carta* Carta jogada
        */
        Carta* jogar_carta_selecionada(unsigned int indice);

        /**
         * @brief Adiciona na mão a carta comprada pelo jogador
         * @param carta_comprada Carta a ser adicionada na mao do jogador
        */
        void comprar_carta(Carta* carta_comprada);

};

#endif