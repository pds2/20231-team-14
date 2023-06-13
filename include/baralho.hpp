#ifndef UNO_BARALHO_HPP
#define UNO_BARALHO_HPP

#include <vector>
#include "cartas.hpp"

class Baralho {
    private:
        unsigned int _numero_de_cartas;
        std::vector<Carta*> _cartas;
    public:
        /*
         * @brief Constrói um baralho em ordem aleatória com todas as cartas de um jogo completo padrão
         */
        Baralho();

        /*
         * @brief Constrói um baralho com as cartas passadas como parâmetro
         */
        Baralho(std::vector<Carta*> x);

        /*
         * @brief Destrói o baralho
         */
        ~Baralho();

        /*
         * @brief Retorna as cartas do baralho
         */
        std::vector<Carta*> get_cartas();

        /*
         * @brief Imprime as cartas do baralho
         */
        void imprimir_baralho();

        /*
         * @brief Retira a carta do topo do baralho e a retorna
         */
        Carta* retirar_topo();
};


#endif