#ifndef UNO_CICLO_HPP
#define UNO_CICLO_HPP

#include "jogador.hpp"

#include <vector>

class IndiceJogadorInvalido_e {};

class Ciclo {
    private:
        std::vector<Jogador*> _jogadores;
        unsigned short _indexJogador;
    public:
        /*
         * @brief Constroi um ciclo
        */
        Ciclo();

        /*
         * @brief Destroi um ciclo
        */
        ~Ciclo();

        /*
         * @brief Adiciona jogadores para o ciclo
        */
        void adicionar_jogadores(Jogador*);

        /*
         * @brief Passa a vez para o proximo jogador
        */
        void proximo_jogador();

        /*
         * @brief Retorna o jogador da rodada
        */
        Jogador* get_jogador_atual();

        /*
         * @brief Inverte a ordem dos jogadores
        */
        void inverter();

        /*
         * @brief Retorna o próximo jogador
        */        
        Jogador* get_proximo_jogador();

        /*
         * @brief Retorna o index
        */
        short get_index();
        
        /*
         * @brief Retorna o jogador "n" do vetor
        */
        Jogador* get_jogador(int);

        /*
         * @brief Retorna o jogador posicionado em determinado índice do vetor
           @throws Lança uma exceção caso não exista um jogador com o índice especificado
        */
        Jogador* get_jogador_por_indice(int indice);
};

#endif