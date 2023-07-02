#ifndef UNO_CARTAS_NUMERICAS_HPP
#define UNO_CARTAS_NUMERICAS_HPP

#include "cartas.hpp"
//#include "monteCartasJogadas.hpp"

class CartasNumericas : public Carta{
    public:
        CartasNumericas();
        CartasNumericas(valor valor, cor cor);
        virtual bool verificar_jogada(Carta* carta);
};

#endif