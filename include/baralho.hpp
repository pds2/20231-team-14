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
         * @brief Constrói um baralho vazio
         */
        Baralho();

        /*
         * @brief Constrói um baralho em ordem aleatória com todas as cartas de um jogo completo padrão
         */
        Baralho(unsigned int numero_de_cartas, std::vector<Carta*> cartas);

        /*
         * @brief Destrói o baralho
         */
        ~Baralho();

        /*
         * @brief Retorna o tamanho do baralho
         */
        unsigned int get_numero_de_cartas();

        /*
         * @brief Altera o número de cartas
        */
        void alterar_numero_cartas(unsigned int novo_numero);

        /*
         * @brief Retorna as cartas do baralho
         */
        std::vector<Carta*> get_cartas();

        /*
         * @brief Retorna a carta cujo índice foi especificado
         */
        Carta* get_carta(unsigned int indice);

        /*
         * @brief Altera as cartas do baralho
         */
        void alterar_cartas(std::vector<Carta*> novas_cartas);

        /*
         * @brief Imprime as cartas do baralho
         */
        void imprimir_baralho();

        /*
         * @brief Embaralha as cartas do baralho
         */
        void embaralhar_cartas();

        /*
         * @brief Retira e retorna a carta no topo do baralho
         */
        Carta* retirar_carta_topo();

        /*
         * @brief Limpa as cartas do baralho
         */
        void limpar_cartas();

};

#endif