#ifndef UNO_SISTEMA_HPP
#define UNO_SISTEMA_HPP

#include "monteCartasIniciais.hpp"
#include "monteCartasComer.hpp"
#include "monteCartasJogadas.hpp"
#include "maoJogador.hpp"
#include "ciclo.hpp"
#include "jogador.hpp"

class PartidaInvalida_e {};

class Sistema{
    private:
        bool _partida_finalizada;
    public:
        /*
         * @brief Constroi um sistema e seta "_partida_finalizada" = false
        */
        Sistema();

        /*
         * @brief Seta "_partida_finalizada" = true
        */
        void finalizar_partida();

        /*
         * @brief Prepara o monte de cartas que será usado para compras
        */
        MonteCartasComer* preparar_monte_cartas_para_compra(MonteCartasIniciais* monte_inicial, int qntd_cartas_iniciais, int qntd_jogadores);
        
        /*
         * @brief Prepara um monte já embaralhado para começar a partida 
        */
        MonteCartasIniciais* preparar_monte_inicial();

        /*
         * @brief Prepara o monte de cartas que serão jogadas
        */
        MonteCartasJogadas* preparar_monte_cartas_jogadas(MonteCartasIniciais* monte_inicial); 

        /*
         * @brief Prepara os jogadores da partida
        */
        void preparar_jogadores(Ciclo* ciclo, MonteCartasIniciais* monte_inicial, int qntd_jogadores, int qntd_cartas_iniciais);

        /*
         * @brief Imprime as informações no início de cada partida
        */
        void imprimir_informacoes_inicio_partida(MonteCartasJogadas* monte_principal);
        
        /*
         * @brief Imprime as informações no início de cada rodada
        */
        void imprimir_informacoes_inicio_rodada(Ciclo* c, MonteCartasJogadas* monte_principal, int rodada, cor cor_atual);
        
        /*
         * @brief Compra uma carta e imprime as informações necessárias 
        */
        void comprar_e_imprimir_informacoes(Ciclo* c, MonteCartasComer* monte_compras, MonteCartasJogadas* monte_principal);
        
        /*
         * @brief Faz a jogada da vez
        */
        void fazer_jogada(Ciclo* c, MonteCartasJogadas* monte_principal, bool& curinga, int indice_carta, cor& cor_atual);

        /*
         * @brief Checa e reincia, se necessário, o monte de compras
        */
        void checar_reinicio_monte_compras(MonteCartasComer* monte_compras, MonteCartasJogadas* monte_principal);
        
        /*
         * @brief Aplica um efeito especial se necessário
        */
        void aplicar_efeito_especial(Ciclo* c, MonteCartasComer* monte_compras, bool& pular_vez, int qntd_jogadores, valor checar_especial);
        
        /*
         * @brief Aplica a mudança de cor do baralho se necessário
        */
        void aplicar_mudanca_cor(MonteCartasJogadas* monte_principal, bool& curinga, cor checar_mudanca_de_cor, cor& cor_atual);
        
        /*
        * @brief O jogo em si. Gerencia a ordem dos jogadores, jogadas de cartas e verifica se alguem venceu a partida
          @throws Lança uma exceção caso a quantidade de jogadores seja negativa/maior do que 9 ou o número de cartas seja insuficiente
        */
        void nova_partida(int qntd_jogadores, int qntd_cartas_iniciais);
};

#endif