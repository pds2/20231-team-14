#ifndef UNO_MONTE_CARTAS_INICIAIS_HPP
#define UNO_MONTE_CARTAS_INICIAIS_HPP

#include "baralho.hpp"

class MonteCartasIniciais : public Baralho {
    public:
        /**
         * @brief Constrói o monte de cartas incial do jogo
         */
        MonteCartasIniciais();

        /**
         * @brief Distribui uma mão inicial para um jogador 
         * @param qtd_cartas_iniciais A quantidade de cartas que serão distribuidas em uma mão
         * @throws Lança uma exceção caso não existam cartas suficientes para serem distribuídas
         * @return std::vector<Carta*> A mão que sera distribuida para um jogador
         */
        std::vector<Carta*> distribuir_mao_inicial(unsigned int qtd_cartas_iniciais);
        // Esse throw nao ta errado nao?

        /**
         * @brief Seleciona e retorna a carta que irá começar o jogo, com exceção da cartas cartas pretas
         * @return Carta* A carta que iniciara o jogo
         */
        Carta* selecionar_carta_inicial();
};

#endif