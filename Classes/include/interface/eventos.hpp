#ifndef EVENTOS_HPP
#define EVENTOS_HPP

#include "cocos2d.h"
#include <vector>

class Eventos{
    private:
        std::vector<std::vector<cocos2d::EventListenerTouchOneByOne*>> touchCartas;
        cocos2d::EventListenerTouchOneByOne* touch_baralho;
        std::vector<cocos2d::EventListenerTouchOneByOne*> touch_cores;
        cocos2d::EventListenerTouchOneByOne* touch_Uno;
    public:
        /**
         * @brief Inicializa os eventos
         * @param qntd_jogadores A quantidade de jogadores na partida
        */
        void cria_eventos_jogar_carta(int qntd_jogadores);

        /**
         * @brief Adiciona o evento de clicar em uma carta
         * @param touchCarta Evento da carta que pode ser clicada pelo jogador
         * @param jogador Indice do jogador da carta
        */
        void adicionar_evento_jogar_carta(cocos2d::EventListenerTouchOneByOne* touchCarta, int jogador);

        /**
         * @brief Remove o evento de clicar em uma carta
         * @param posicao_carta Posição da carta que terá o seu evento removido 
         * @param jogador Indice do jogador da carta
        */
        void remover_evento_jogar_carta(int posicao_carta, int jogador);

        /**
         * @brief Retorna o evento de clicar em uma carta
         * @param indice Posição da carta  que será jogada
         * @param jogador Indice do jogador da carta
         * @return Event listener de click na carta especificada
        */
        cocos2d::EventListenerTouchOneByOne* get_evento_jogar_carta(int indice, int jogador);

        /**
         * @brief Adiciona o evento de cliar no baralho
         * @param touchBaralho Evento do baralho clicável
        */
        void adicionar_evento_comprar_carta(cocos2d::EventListenerTouchOneByOne* touchBaralho);

        /**
         * @brief Retorna o evento de clicar na baralho
         * @return Event listener do click no baralho
        */
       cocos2d::EventListenerTouchOneByOne* get_evento_comprar_carta();

        /**
         * @brief Adiciona o evento de escolher uma cor
         * @param touchCor Evento de clicar em uma das cores possíveis de selecionar
        */
       void adicionar_evento_escolha_cor(cocos2d::EventListenerTouchOneByOne* touchCor);

       /**
        * @brief Retorna o evento de escolha de uma cor
        * @param indice Indice do quadrado da cor escoljida
        * @return Evento de clicar em um dos quadrados
       */
       cocos2d::EventListenerTouchOneByOne* get_evento_escolha_cor(int indice);

       /**
        * @brief Limpa os eventos de escolha de cor
       */
      void clear_evento_escolha_cor();

      /**
       * @brief Adiciona o evento de gritar Uno
      */
      void adicionar_evento_gritar_Uno(cocos2d::EventListenerTouchOneByOne* touchUno);

      /**
       * @brief Retorna o evento de gritar Uno
      */
      cocos2d::EventListenerTouchOneByOne* get_evento_gritar_Uno();
    
    

};
#endif