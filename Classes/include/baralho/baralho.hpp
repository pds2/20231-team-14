#ifndef UNO_BARALHO_HPP
#define UNO_BARALHO_HPP

#include <vector>
#include "../cartas/cartas.hpp"
#include "../cartas/cartasNumericas.hpp"
#include "../cartas/cartasEspeciais.hpp"
#include "../cartas/cartasEspeciaisPretas.hpp"

class IndiceInvalido_e {};

class NumeroCartasInvalido_e {};

class Baralho {
    private:
        unsigned int _numero_de_cartas;
        std::vector<Carta*> _cartas;
    public:
        /**
         * @brief Constrói um baralho vazio
         */
        Baralho();

        /**
         * @brief Constrói um baralho com todas as cartas passadas como parâmetro
         * @param numero_de_cartas Numero de cartas do baralho
         * @param cartas As cartas do abralho
         */
        Baralho(unsigned int numero_de_cartas, std::vector<Carta*> cartas);

        /**
         * @brief Destrói o baralho
         */
        ~Baralho();

        /**
         * @brief Retorna o tamanho do baralho
         * @return unsigned int Numero de cartas contidas no baralho
         */
        unsigned int get_numero_de_cartas();

        /**
         * @brief Retorna as cartas do baralho
         * @return std::vector<Carta*> Cartas do baralho
         */
        std::vector<Carta*> get_cartas();

        /**
         * @brief Retorna a carta cujo índice foi especificado
         * @param indice Posicao da carta no baralho
         * @throws Lança uma exceção caso não exista uma carta com o índice indicado
         */
        Carta* get_carta(unsigned int indice);
        
        /**
         * @brief Imprime as cartas do baralho
         * @return c->imprime_carta() Impressao de cada carta do baralho
         */
        void imprimir_baralho();

        /**
         * @brief Altera o número de cartas
         * @param novo_numero Novo numero de cartas do baralho
         * @throws Lança uma exceção caso o número de cartas seja maior do que o existente em um baralho
        */
        void alterar_numero_cartas(unsigned int novo_numero);

        /**
         * @brief Altera as cartas do baralho
         * @param novas_cartas As novas cartas do baralho
         */
        void alterar_cartas(std::vector<Carta*> novas_cartas);

        /**
         * @brief Embaralha as cartas do baralho
         */
        void embaralhar_cartas();

        /**
         * @brief Limpa as cartas do baralho
         */
        void limpar_cartas();

};

#endif