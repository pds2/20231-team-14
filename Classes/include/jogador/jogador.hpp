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
        bool _pediu_uno;
    public:
        /**
         * @brief Constrói um jogador com 7 cartas em mãos
         * @param id Id do jogador
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
         * @brief Define se o jogador é um bot
         * @return false Falso, jogador nao e um bot
        */
        virtual bool is_bot();

        /**
         * @brief Recebe cartas
         * @param mao A nova mao de cartas para o jogador
        */
        void receber_cartas(MaoJogador* mao);
        
        /**
         * @brief Imprime a mão de um jogador
         */
        void imprimir_mao();

        /**
         * @brief Joga a carta especificada pelo índice, caso a jogada seja válida
         * @param indice Indice da carta que vai ser jogada
         * @param carta_topo A carta no topo do monte de cartas jogadas
         * @throws Lança uma exceção caso a carta selecionada não possa ser jogada
         * @return Carta* A carta que foi jogada
         */
        virtual Carta* jogar_carta(unsigned int indice, Carta* carta_topo);

        /**
         * @brief Joga a carta especificada pelo índice, caso a jogada seja válida (analisando somente a cor do coringa)
         * @param indice Indice da carta que vai ser jogada
         * @param curinga A cor definida pelo coringa
         * @throws Lança uma exceção caso a carta selecionada não possa ser jogada
         * @return Carta* A carta que foi jogada
         */
        virtual Carta* jogar_carta_apenas_pela_cor(unsigned int indice, cor curinga);

        /**
        * @brief Vence o jogo quando chegar a 0 cartas.
        * @return true Verdadeiro se o jogador estiver com 0 cartas
        * @return false Falso caso o jogador ainda tenha cartas
        */
        bool verificar_vitoria();

        /**
        * @brief Retorna id.
        * @return unsigned int Id do jogador.
        */
        int get_id();

        /**
         * @brief Retorna a mão do jogador.
         * @return MaoJogador* A mao de cartas do jogador
        */
        MaoJogador* get_mao();

        /**
         * @brief Retorna uma cor não preta de uma das cartas da mão do jogador
         * @return cor A cor da carta escolhida caso ela não seja preta
         * @return cor(0) Caso todas as cartas sejam pretas
        */
        cor get_cor_carta_mao();

        /**
         * @brief Seta 'uno' do jogador.
        */
        void set_pedir_uno(bool uno);

        /**
         * @brief Retorna pedir uno.
        */
        bool is_pediu_uno();
       
};

#endif