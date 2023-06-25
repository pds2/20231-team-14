#ifndef UNO_MONTE_CARTAS_JOGADAS_HPP
#define UNO_MONTE_CARTAS_JOGADAS_HPP

#include "baralho.hpp"

class MonteCartasJogadas: public Baralho {
    public:
        /*
         * @brief Constrói o monte que receberá as cartas jogadas
        */
        MonteCartasJogadas(std::vector<Carta*> carta_inicial);

        /*
         * @brief Revela a carta da vez a qual está no topo
        */
        Carta* mostrar_topo();

        /*
         * @brief Adiciona uma carta no topo do monte (ou seja, efetua a jogada de um participante)
        */
        void adicionar_carta_topo(Carta* carta_jogada);
};

#endif