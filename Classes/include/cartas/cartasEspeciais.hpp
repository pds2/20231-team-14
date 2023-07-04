#ifndef UNO_CARTAS_ESPECIAIS_HPP
#define UNO_CARTAS_ESPECIAIS_HPP

#include "cartasNumericas.hpp"

class CartasEspeciais : public CartasNumericas{
    public:
        bool block();
        virtual bool come();
        bool inverte();
};



#endif