#ifndef UNO_MONTE_CARTAS_JOGADAS_HPP
#define UNO_MONTE_CARTAS_JOGADAS_HPP

#include "baralho.hpp"

class MonteCartasJogadas: public Baralho {
    public:
        /**
         * @brief Constrói o monte que receberá as cartas jogadas
         * @param carta_inicial A carta que ira começar o jogo
        */
        MonteCartasJogadas(std::vector<Carta*> carta_inicial);
        
        /**
         * @brief Constrói um monte vazio
        */
        MonteCartasJogadas();

        /**
         * @brief Revela a carta da vez a qual está no topo
         * @return Carta* A carta que está no topo
        */
        Carta* mostrar_topo();

        /**
         * @brief Adiciona uma carta no topo do monte (ou seja, efetua a jogada de um participante)
        */
        void adicionar_carta_topo(Carta* carta_jogada);
        
};

#endif