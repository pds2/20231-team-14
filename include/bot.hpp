#ifndef UNO_BOT_HPP
#define UNO_BOT_HPP

#include "jogador.hpp"
#include <thread>

class Sistema;

class Bot : public Jogador {
    private:
        bool _sem_cartas; //verdadeiro caso nenhuma carta em mao possa ser jogada
    public: 
        /*
         * @brief Constrói um jogador com 7 cartas em mãos
         */
        Bot(unsigned int id);

        /**
         * @brief Construi um jogador vazio
        */
        //Bot();

        /**
         * @brief Destroi a mão do jogador
        */
        //~Bot();

        Carta* jogar_carta(unsigned int indice, Carta* carta_topo) override;
};

#endif