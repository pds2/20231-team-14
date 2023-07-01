#ifndef UNO_SISTEMA_HPP
#define UNO_SISTEMA_HPP

#include "../include/monteCartasIniciais.hpp"
#include "../include/monteCartasComer.hpp"
#include "../include/monteCartasJogadas.hpp"
#include "../include/maoJogador.hpp"
#include "../include/ciclo.hpp"
#include "../include/jogador.hpp"

class Sistema{
    private:
        bool _partida_finalizada;
        

    public:
        /*
         * @brief Constroi o sistema e seta "_partida_finalizada" = false.
        */
        Sistema();
        /*
         * @brief Seta "_partida_finalizada" = true.
        */
        void finalizar_partida();
        /*
        * @brief O jogo em si. Gerencia a ordem dos jogadores, jogadas de cartas e se alguem venceu a partida
        */
        void nova_partida(int qntd_jogadores);
};

#endif