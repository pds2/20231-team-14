#ifndef UNO_MONTE_CARTAS_INICIAIS_HPP
#define UNO_MONTE_CARTAS_INICIAIS_HPP

#include "baralho.hpp"

class MonteCartasIniciais : public Baralho {
    public:
        /*
         * @brief Constrói o monte de cartas incial do jogo
         */
        MonteCartasIniciais();

        /*
         * @brief Distribui uma mão inicial para um jogador 
           @throws Lança uma exceção caso não existam cartas suficientes para serem distribuídas
         */
        std::vector<Carta*> distribuir_mao_inicial(unsigned int qtd_cartas_iniciais);

        /*
         * @brief Seleciona e retorna a carta que irá começar o jogo, com exceção da carta "Mais Quatro"
         */
        Carta* selecionar_carta_inicial();
};

#endif