#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include "../../include/cartas/cartas.hpp"
#include "../../include/baralho/monteCartasComer.hpp"
#include "../../include/baralho/monteCartasIniciais.hpp"
#include "../../include/baralho/monteCartasJogadas.hpp"
#include "../../include/baralho/maoJogador.hpp"
#include "../../include/jogador/jogador.hpp"
#include "../../include/jogador/bot.hpp"
#include "ciclo.hpp"
#include <iostream>
#include <vector>

class PartidaInvalida_e {};
class CartaNaoPertence_e {};

class Sistema {
    public:

        /**
         * @brief Inicializa o Sistema do jogo, incluindo os jogadores, a ordem dos jogadores e todos os baralhos
         * @throws Lança uma exceção caso a quantidade de jogadores seja negativa/maior do que 9 ou o número de cartas seja insuficiente
        */
        Sistema(int qntd_jogadores, int qntd_cartas_iniciais);

        /**
         * @brief Destroi os montes de cartas e o ciclo após o fim do sistema
        */
        ~Sistema();

        /**
        * @brief Seta a carta coringa
        */
        void setar_curinga();

        /*
         * @brief Prepara um monte já embaralhado para começar a partida 
        */
        MonteCartasIniciais* preparar_monte_inicial();

        /** 
         * @brief Prepara o monte de cartas que será usado para compras
        */
        void preparar_monte_cartas_para_compra(MonteCartasIniciais* monte_inicial);

        /**
        * @brief Prepara o monte de cartas que serão jogadas
        */
        void preparar_monte_cartas_jogadas(MonteCartasIniciais* monte_inicial); 

        /**
         * @brief Prepara os jogadores da partida
        */
        void preparar_jogadores(MonteCartasIniciais* monte_inicial);

        /**
         *@brief Compra uma carta do baralho
        */
        void comprar_carta();

        /**
        * @brief Checa e reincia, se necessário, o monte de compras
        */
        void checar_reinicio_monte_compras();

        /**
         * @brief Recebe uma carta e verifica se ela existe na mão do jogador
         * @throws Manda uma exceção quando não encontra a carta na mão do jogador
        */
        int definir_indice_carta_jogada(Carta *carta_clicada);

        /**
         *@brief Joga a carta se for possível
        */
        bool jogar_carta(int posicao_carta_mao);

        /**
         *@brief Verifica se é necessário mudar de cor
        */
        bool checa_mudanca_cor();

        /**
         * @brief Aplica o efeito especial das cartas
        */
        int aplicar_efeito_especial();

        /**
         * @brief Distribuir a quantidade de cartas compradas pelo proximo jogador
        */
        void comprar_carta_proximo_jogador(int quantidade_cartas);

        /**
         *@brief Retorna a quantidade de jogadores
        */
        int get_quantidade_jogadores();

        /**
         *@brief Retorna o ciclo de jogadores da partida
        */
        Ciclo* get_ciclo();
        
        /**
         *@brief Retorna o monte de cartas jogadas 
        */
        MonteCartasJogadas* get_monte_jogadas();

        /**
         *@brief Retorna o monte de cartas para comprar
        */
        MonteCartasComer* get_monte_compras();

        /**
         *@brief Define a cor atual escolhida após a jogada do curinga
        */
        void set_cor_atual(cor cor_atual);

    private:
        bool curinga;
        cor cor_atual;
        int qntd_jogadores;
        int qntd_cartas_iniciais;
        Ciclo *c;
        MonteCartasJogadas *monte_principal;
        MonteCartasComer *monte_compras;
};

#endif
