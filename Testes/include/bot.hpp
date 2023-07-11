#ifndef UNO_BOT_HPP
#define UNO_BOT_HPP

#include <thread>
#include "jogador.hpp"

class Bot : public Jogador {
    private:
        bool _sem_cartas; //Verdadeiro caso nenhuma carta em mão possa ser jogada

    public: 
        /**
         * @brief Constrói um bot
         */
        Bot(unsigned int id);

        /**
         * @brief Realiza uma jogada automaticamente pelo bot.
         *        Na versão com a interface, é necessário que o jogador humano
         *        faça a jogada manualmente
        */
        Carta* jogar_carta(unsigned int indice, Carta* carta_topo) override;
};

#endif