#ifndef EVENTOS_HPP
#define EVENTOS_HPP

#include "cocos2d.h"
#include <vector>

class Eventos{
    public:

        /**
         * @brief Inicializa os eventos
        */
        void cria_eventos_jogar_carta(int qntd_jogadores);

        /**
         * @brief Adiciona o evento de clicar em uma carta
        */
        void adicionar_evento_jogar_carta(cocos2d::EventListenerTouchOneByOne* touchCarta, int jogador);

        /**
         * @brief Remove o evento de clicar em uma carta
        */
        void remover_evento_jogar_carta(int posicao_carta, int jogador);

        /**
         * @brief Retorna o evento de clicar em uma carta
        */
        cocos2d::EventListenerTouchOneByOne* get_evento_jogar_carta(int indice, int jogador);

        /**
         * @brief Adiciona o evento de cliar no baralho
        */
        void adicionar_evento_comprar_carta(cocos2d::EventListenerTouchOneByOne* touchBaralho);

        /**
         * @brief Retorna o evento de clicar na carta
        */
       cocos2d::EventListenerTouchOneByOne* get_evento_comprar_carta();

        /**
         * @brief Adiciona o evento de escolher uma cor
        */
       void adicionar_evento_escolha_cor(cocos2d::EventListenerTouchOneByOne* touchCor);

       /**
        * @brief Retorna o evento de escolha de uma cor
       */
       cocos2d::EventListenerTouchOneByOne* get_evento_escolha_cor(int indice);

       /**
        * @brief Limpa os eventos de escolha de cor
       */
      void clear_evento_escolha_cor();
    
    private:
        std::vector<std::vector<cocos2d::EventListenerTouchOneByOne*>> touchCartas;
        cocos2d::EventListenerTouchOneByOne* touch_baralho;
        std::vector<cocos2d::EventListenerTouchOneByOne*> touch_cores;

};
#endif