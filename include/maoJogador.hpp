#ifndef UNO_MAO_JOGADOR_HPP
#define UNO_MAO_JOGADOR_HPP

#include "baralho.hpp"

class MaoJogador : public Baralho {
    public:
        /*
         * @brief Constrói a mão vazia de um jogador
        */
        MaoJogador();

        /*
         * @brief Constrói a mão do início de cada partida
        */
        MaoJogador(unsigned int qtd_cartas_inicial, std::vector<Carta*> mao_inicial);

        /*
         * @brief Retira da mão a carta com o índice especificado
           @throws Lança uma exceção caso não exista uma carta com o índice indicado
        */
        Carta* jogar_carta_selecionada(unsigned int indice);

        /*
         * @brief Adiciona na mão a carta comprada pelo jogador
        */
        void comprar_carta(Carta* carta_comprada);
};

#endif