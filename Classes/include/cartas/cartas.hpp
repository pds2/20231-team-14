#ifndef UNO_CARTAS_HPP
#define UNO_CARTAS_HPP

#include <string>

enum valor {
    N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, INVERTE_ORDEM, PULA_VEZ, MAIS_DOIS, MAIS_QUATRO, CURINGA
};

enum cor {
    VERMELHO, VERDE, AZUL, AMARELO, PRETA
};

class ValorInvalido_e{};

class CorInvalida_e {};

class Carta {
    private:
        valor _valor;
        cor _cor;
    public:
        /**
         * @brief Constrói uma carta de UNO 
         */
        Carta();

        /**
         * @brief Constrói uma carta de UNO com valor e cor especificados
         * @param valor Numero da carta
         * @param cor Cor da carta
         */
        Carta(valor valor, cor cor);
        
        /**
         * @brief Retorna o valor de uma carta de UNO
         * @return valor Numero da carta
         */
        valor get_valor();
        
        /**
         * @brief Retorna a cor de uma carta de UNO
         * @return cor Cor da carta
         */
        cor get_cor();

        /**
         * @brief Imprime os valores da carta
         */
        void imprime_carta();

        /**
         * @brief Muda o valor de uma carta de UNO
         * @throws Lança uma exceção caso o valor esteja fora das opções possíveis
         */
        void muda_valor(unsigned int val);

        /**
         * @brief Muda a cor de uma carta de UNO
         * @throws Lança uma exceção caso a cor esteja fora das opções possíveis
         */
        void muda_cor(unsigned int c);

        /**
         * @brief Retorna o sprite da carta
         */
        std::string get_sprite();

        //virtual bool verificar_jogada(MonteCartasJogadas);

        
};

#endif