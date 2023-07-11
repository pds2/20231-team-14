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
#include <vector>

class PartidaInvalida_e {};
class CartaNaoPertence_e {};

class Sistema {
    private:
        bool curinga;
        cor cor_atual;
        int qntd_jogadores;
        int qntd_cartas_iniciais;
        Ciclo *c;
        MonteCartasJogadas *monte_principal;
        MonteCartasComer *monte_compras;
    public:

        /**
         * @brief Inicializa o Sistema do jogo, incluindo os jogadores, a ordem dos jogadores e todos os baralhos
         * @param qntd_jogadores Quantidade de jogadorews na partida
         * @param qntd_cartas_iniciais Quantidade de cartas que cada jogador recebe no inicio
         * @throws Lança uma exceção caso a quantidade de jogadores seja negativa/maior do que 9 ou o número de cartas seja insuficiente
        */
        Sistema(int qntd_jogadores, int qntd_cartas_iniciais);

        /**
        * @brief Seta a carta coringa
        */
        void setar_curinga();

        /**
         * @brief Prepara um monte já embaralhado para começar a partida 
         * @return MonteCartasIniciais* O monte de cartas
        */
        MonteCartasIniciais* preparar_monte_inicial();

        /** 
         * @brief Prepara o monte de cartas que será usado para compras
         * @param monte_inicial O monte das cartas iniciais que serao usados para criar o monte de compra
        */
        void preparar_monte_cartas_para_compra(MonteCartasIniciais* monte_inicial);

        /**
        * @brief Prepara o monte de cartas que serão jogadas
        * @param monte_inicial O monte das cartas jogadas que serao usados para criar o monte de compra
        */
        void preparar_monte_cartas_jogadas(MonteCartasIniciais* monte_inicial); 

        /**
         * @brief Prepara os jogadores da partida
         * @param monte_inicial Da a cada jogador um conjunto de cartas do monte inicial
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
         * @param carta_clicada A carta que o jogador escolheu
         * @throws Manda uma exceção quando não encontra a carta na mão do jogador
         * @return int Posicao da carta
        */
        int definir_indice_carta_jogada(Carta *carta_clicada);

        /**
         * @brief Joga a carta se for possível
         * @param posicao_carta_mao Indice da carta que será jogada
        */
        void jogar_carta(int posicao_carta_mao);

        /**
         * @brief Verifica se é necessário mudar de cor
         * @return true Verdadeiro caso a carta do topo das cartas jogadas tenha cor preta
         * @return false Falso caso contrario
        */
        bool checa_mudanca_cor();

        /**
         * @brief Aplica o efeito especial das cartas
         * @return int Retorna a quantidade de cartas para comprar
        */
        int aplicar_efeito_especial();

        /**
         * @brief Distribuir a quantidade de cartas compradas pelo proximo jogador
         * @param quantidade_cartas A quantidade de cartas que sera compradas
        */
        void comprar_carta_proximo_jogador(int quantidade_cartas);

        /**
         * @brief Retorna a quantidade de jogadores
         * @return int Quantidade de jogadores
        */
        int get_quantidade_jogadores();

        /**
         * @brief Retorna o ciclo de jogadores da partida
         * @return Ciclo* O ciclo de jogadores
        */
        Ciclo* get_ciclo();
        
        /**
         * @brief Retorna o monte de cartas jogadas 
         * @return MonteCartasJogadas* O monte principal
        */
        MonteCartasJogadas* get_monte_jogadas();

        /**
         * @brief Retorna o monte de cartas para comprar
         * @return MonteCartasComer* O monte de comer cartas
        */
        MonteCartasComer* get_monte_compras();

        /**
         * @brief Define a cor atual escolhida após a jogada do curinga
         * @param cor_atual A cor escolhida para ser a nova cor atual
        */
        void set_cor_atual(cor cor_atual);

        /**
         * @brief Destroi os montes de cartas e o ciclo após o fim do sistema
        */
        ~Sistema();
};

#endif
