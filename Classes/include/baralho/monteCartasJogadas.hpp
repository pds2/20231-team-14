#ifndef UNO_MONTE_CARTAS_JOGADAS_HPP
#define UNO_MONTE_CARTAS_JOGADAS_HPP

#include "baralho.hpp"
#include "cocos2d.h"

class MonteCartasJogadas: public Baralho {
    private:
        cocos2d::Sprite* carta_jogada;
    public:
        /*
         * @brief Constrói o monte que receberá as cartas jogadas
        */
        MonteCartasJogadas(std::vector<Carta*> carta_inicial);
        
        /**
         * @brief Constrói um monte vazio
        */
        MonteCartasJogadas();

        /*
         * @brief Revela a carta da vez a qual está no topo
        */
        Carta* mostrar_topo();

        /*
         * @brief Adiciona uma carta no topo do monte (ou seja, efetua a jogada de um participante)
        */
        void adicionar_carta_topo(Carta* carta_jogada);

        /**
         * @brief Cria o sprite da carta no topo para mostra-lo na tela
        */
        void criar_inteface_monte_jogadas(cocos2d::Size visibleSize, cocos2d::Vec2 origin);

        /**
         * @brief Retorna o sprite da carta no topo para mostra-lo na tela
        */
        cocos2d::Sprite* get_inteface_monte_jogadas();

        /**
         * @brief Define o sprite da carta jogada mostrada na tela
        */
        void set_inteface_monte_jogadas(cocos2d::Sprite* sprite);
        
};

#endif