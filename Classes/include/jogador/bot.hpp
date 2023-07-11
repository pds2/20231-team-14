#ifndef UNO_BOT_HPP
#define UNO_BOT_HPP

#include<cstdlib>      
#include "jogador.hpp"

class Bot : public Jogador {
    public:
        Bot(unsigned int id);
        Carta* jogar_carta(unsigned int indice, Carta* carta_topo) override;
        Carta* jogar_carta_apenas_pela_cor(unsigned int indice, cor curinga) override;
        bool is_bot() override;
        void grita_uno_aleatoriamente();
};

#endif