#ifndef UNO_JOGADOR_HPP
#define UNO_JOGADOR_HPP

#include "baralho.hpp"

class Jogador {
    private:
        unsigned int _numero_de_cartas_na_mao;
        std::vector<Carta*> _mao;
    public:
        /*
         * @brief Constrói um jogador com 7 cartas em mãos
         */
        Jogador(std::vector<Carta*> mao);
        
        /*
         * @brief Imprime a mão de um jogador
         */
        void imprimir_mao();

        /*
         * @brief Joga a carta especificada pelo índice
         */
        Carta* jogar_carta(unsigned int indice);
};

#endif