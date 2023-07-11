#ifndef UNO_CICLO_HPP
#define UNO_CICLO_HPP

#include "../jogador/jogador.hpp"

#include <vector>

class IndiceJogadorInvalido_e {};
class Ciclo {
    private:
        std::vector<Jogador*> _jogadores;
        unsigned short _indexJogador;
    public:
        /**
         * @brief Constroi um ciclo
        */
        Ciclo();

         /**
         * @brief Destroi um ciclo
        */
        ~Ciclo();

        /**
         * @brief Adiciona jogadores para o ciclo
         * @param j Adiciona um jogador ao ciclo do jogo
        */
        void adicionar_jogadores(Jogador* j);

        /**
         * @brief Passa a vez para o proximo jogador
        */
        void proximo_jogador();

        /**
         * @brief Retorna o jogador da rodada
         * @return Jogador* Jogador da rodada
        */
        Jogador* get_jogador_atual();

        /**
         * @brief Inverte a ordem dos jogadores
        */
        void inverter();

        /**
         * @brief Retorna o próximo jogador
         * @return Jogador* O jogador da proxima rodada
        */        
        Jogador* get_proximo_jogador();

        /**
         * @brief Retorna o index
         * @return unsigned short Index atual do ciclo
        */
        short get_index();
        
        /**
         * @brief Retorna o jogador "n" do vetor
         * @param i Indice do jogador
         * @return Jogador* O jogador de indice "n"
         * @return nullptr Não foi encontrado o jogador
        */
        Jogador* get_jogador(int i);

        /**
         * @brief Retorna o jogador posicionado em determinado índice do vetor
         * @param indice Indice do jogador
         * @throws Lança uma exceção caso não exista um jogador com o índice especificado
         * @return Jogador* O jogador de indice "n"
        */
        Jogador* get_jogador_por_indice(int indice);
};

#endif