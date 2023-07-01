#ifndef UNO_JOGADOR_HPP
#define UNO_JOGADOR_HPP

#include "baralho.hpp"
#include "maoJogador.hpp"

class Jogador {
    private:
        unsigned int _numero_de_cartas_na_mao;
        MaoJogador* _mao;
        unsigned int _id; //apenas para testes da classe "ciclo"
    public:
        /*
         * @brief Constrói um jogador com 7 cartas em mãos
         */
        Jogador(unsigned int id);
        
        /*
         * @brief recebe cartas
        */
        void receber_cartas(MaoJogador*);

        /*
         * @brief Imprime a mão de um jogador
         */
        void imprimir_mao();

        /*
         * @brief Joga a carta especificada pelo índice
         */
        Carta* jogar_carta(unsigned int indice);

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
};

#endif