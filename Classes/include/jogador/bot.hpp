#ifndef UNO_BOT_HPP
#define UNO_BOT_HPP

#include<cstdlib>      
#include "jogador.hpp"

class Bot : public Jogador {
    public:

        /**
         * @brief Constrói um bot com 7 cartas em mãos
         * @param id Id do bot
         */
        Bot(unsigned int id);

        /**
         * @brief Joga a carta especificada pelo índice, caso a jogada seja válida
         * @param indice Indice da carta que vai ser jogada
         * @param carta_topo A carta no topo do monte de cartas jogadas
         * @throws Lança uma exceção caso a carta selecionada não possa ser jogada
         * @return Carta* A carta que foi jogada
        */
        Carta* jogar_carta(unsigned int indice, Carta* carta_topo) override;

        /**
         * @brief Joga a carta especificada pelo índice, caso a jogada seja válida (analisando somente a cor do coringa)
         * @param indice Indice da carta que vai ser jogada
         * @param curinga A cor definida pelo coringa
         * @throws Lança uma exceção caso a carta selecionada não possa ser jogada
         * @return Carta* A carta que foi jogada
         */
        Carta* jogar_carta_apenas_pela_cor(unsigned int indice, cor curinga) override;

        /**
         * @brief Define se o jogador é um bot
         * @return true Verdadeiro, jogador é um bot
        */
        bool is_bot() override;
        void grita_uno_aleatoriamente();
};

#endif