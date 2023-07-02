#ifndef UNO_SISTEMA_HPP
#define UNO_SISTEMA_HPP

#include "monteCartasIniciais.hpp"
#include "monteCartasComer.hpp"
#include "monteCartasJogadas.hpp"
#include "maoJogador.hpp"
#include "ciclo.hpp"
#include "jogador.hpp"

class Sistema{
    private:
        bool _partida_finalizada;
    public:
        /*
         * @brief Constroi um sistema e seta "_partida_finalizada" = false.
        */
        Sistema();

        /*
         * @brief Seta "_partida_finalizada" = true.
        */
        void finalizar_partida();
        
        /*
        * @brief O jogo em si. Gerencia a ordem dos jogadores, jogadas de cartas e verifica se alguem venceu a partida
        */
        void nova_partida(int qntd_jogadores);
};

#endif