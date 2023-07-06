#ifndef UNO_MONTE_CARTAS_COMER_HPP
#define UNO_MONTE_CARTAS_COMER_HPP

#include "baralho.hpp"
#include "cocos2d.h"

class NumeroCartasInsuficientes_e {};

class MonteCartasComer : public Baralho {
    private:
        cocos2d::Sprite* cartasComerSprite;
    public:
        /*
         * @brief Constrói o monte de cartas para comer inicial da partida
        */
        MonteCartasComer(unsigned int numero_cartas_iniciais, int qtd_jogadores, std::vector<Carta*> cartas_restantes);

        /**
         * @brief Constrói um baralho vazio de cartas
        */
        MonteCartasComer();

        /*
         * @brief Checa se é necessário reiniciar o monte caso as cartas tenham se esgotado.
                  Retorna 1 caso seja necessário, 0 caso contrário.
        */
        bool checar_reinicio();

        /*
         * @brief Reinicia o monte, adicionando a ele, de forma embaralhada, as cartas recebidas do monte de cartas jogadas 
        */
        void reiniciar_monte(std::vector<Carta*> cartas_restantes);

        /*
         * @brief Remove a carta do topo do monte e a retorna 
        */
        Carta* comer_carta();

        /*
         * @brief Criar o sprite do baralho
        */
        void criar_interface_monte_comer(cocos2d::Size visibleSize, cocos2d::Vec2 origin);

        /*
         * @brief Retorna o sprite do monte para imprimi-lo na tela 
        */
        cocos2d::Sprite* get_interface_monte_comer();      

};

#endif