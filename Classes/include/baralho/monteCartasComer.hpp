#ifndef UNO_MONTE_CARTAS_COMER_HPP
#define UNO_MONTE_CARTAS_COMER_HPP

#include "baralho.hpp"

class NumeroCartasInsuficientes_e {};

class MonteCartasComer : public Baralho {
    public:
        /**
         * @brief Constrói o monte de cartas para comer inicial da partida
         * @param numero_cartas_iniciais Numero de cartas no monte
         * @param qtd_jogadores Quantidade de jogadores na partida
         * @param cartas_restantes Cartas que sobraram apos a distribuicao inicial das cartas
        */
        MonteCartasComer(unsigned int numero_cartas_iniciais, int qtd_jogadores, std::vector<Carta*> cartas_restantes);

        /**
         * @brief Constrói um baralho vazio de cartas
        */
        MonteCartasComer();

        /**
         * @brief Checa se é necessário reiniciar o monte caso as cartas tenham se esgotado.
         * @return true Verdadeiro caso o monte tenha 0 cartas
         * @return false Falso caso contrário
        */
        bool checar_reinicio();

        /**
         * @brief Reinicia o monte, adicionando a ele, de forma embaralhada, as cartas recebidas do monte de cartas jogadas
         * @param cartas_restantes Cartas do monte de cartas jogadas que se tornaram disponiveis para compra
        */
        void reiniciar_monte(std::vector<Carta*> cartas_restantes);

        /**
         * @brief Remove a carta do topo do monte e a retorna 
         * @throws Lança uma exceção caso o monte esteja sem cartas
         * @return Carta* A carta do topo que foi retirada do monte
        */
        Carta* comer_carta();   

};

#endif