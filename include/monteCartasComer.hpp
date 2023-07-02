#ifndef UNO_MONTE_CARTAS_COMER_HPP
#define UNO_MONTE_CARTAS_COMER_HPP

#include "baralho.hpp"

class MonteCartasComer : public Baralho {
    public:
        /*
         * @brief Constrói o monte de cartas para comer inicial da partida
        */
        MonteCartasComer(unsigned int numero_cartas_iniciais, int qtd_jogadores, std::vector<Carta*> cartas_restantes);

        /*
         * @brief Checa se é necessário reiniciar o monte caso as cartas tenham se esgotado.
                  Retorna 1 caso seja necessário, 0 caso contrário.
        */
        bool checar_reinicio();

        /*
         * @brief Reinicia o monte, adicionando a ele, de forma embaralhada, as cartas recebidas do monte de cartas jogadas 
        */
        void reiniciar_monte(std::vector<Carta*> cartas_restantes);

        /*
         * @brief Remove a carta do topo do monte e a retorna 
        */
        Carta* comer_carta();
};

#endif