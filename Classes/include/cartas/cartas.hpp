#ifndef UNO_CARTAS_HPP
#define UNO_CARTAS_HPP

enum valor {
    N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, INVERTE_ORDEM, PULA_VEZ, MAIS_DOIS, MAIS_QUATRO, CURINGA
};

enum cor {
    VERMELHO, VERDE, AZUL, AMARELO, PRETA
};

class Carta {
    private:
        valor _valor;
        cor _cor;
    public:
        /*
         * @brief Constrói uma carta de UNO 
         */
        Carta();

        /*
         * @brief Constrói uma carta de UNO com valor e cor especificados
         */
        Carta(valor valor, cor cor);
        
        /*
         * @brief Retorna o valor de uma carta de UNO
         */
        valor get_valor();
        
        /*
         * @brief Retorna a cor de uma carta de UNO
         */
        cor get_cor();

        /*
         * @brief Imprime os valores da carta
         */
        void imprime_carta();

        /*
         * @brief Muda o valor de uma carta de UNO
         */
        void muda_valor(unsigned int x);

        /*
         * @brief Muda a cor de uma carta de UNO
         */
        void muda_cor(unsigned int x);

        
};

#endif