#ifndef UNO_JOGADOR_HPP
#define UNO_JOGADOR_HPP

#include "../baralho/baralho.hpp"
#include "../baralho/maoJogador.hpp"
#include "../baralho/monteCartasJogadas.hpp"
#include "../baralho/monteCartasComer.hpp"

class JogadaInvalida_e {};
class Jogador {
    private:
        unsigned int _numero_de_cartas_na_mao;
        MaoJogador* _mao;
        unsigned int _id; //apenas para testes da classe "ciclo"
    public:
        /*
         * @brief Constrói um jogador com 7 cartas em mãos
         */
        Jogador(unsigned int id);

        /**
         * @brief Construi um jogador vazio
        */
        Jogador();

        /**
         * @brief Destroi a mão do jogador
        */
        ~Jogador();

        /**
         * @brief Define se é um jogador ou um bot
        */
        virtual bool is_bot();

        /*
         * @brief Recebe cartas
        */
        void receber_cartas(MaoJogador*);
        
        /*
         * @brief Imprime a mão de um jogador
         */
        void imprimir_mao();

        /**
         * @brief Joga a carta especificada pelo índice, caso a jogada seja válida
         * @throws Lança uma exceção caso a carta selecionada não possa ser jogada
         */
        virtual Carta* jogar_carta(unsigned int indice, Carta* carta_topo);

        /**
         * @brief Joga a carta especificada pelo índice, caso a jogada seja válida (analisando somente a cor do coringa)
         * @throws Lança uma exceção caso a carta selecionada não possa ser jogada
         */
        virtual Carta* jogar_carta_apenas_pela_cor(unsigned int indice, cor curinga);

        /**
        * @brief Vence o jogo quando chegar a 0 cartas.
        */
        bool verificar_vitoria();

        /*
        * @brief Retorna id.
        */
        int get_id();

        /*
         * @brief Retorna a mão do jogador.
        */
        MaoJogador* get_mao();

        /**
         * @brief Retorna uma cor não preta de uma das cartas da mão do jogador
        */
       cor get_cor_carta_mao();
       
};

#endif