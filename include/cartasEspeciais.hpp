#ifndef UNO_CARTAS_ESPECIAIS_HPP
#define UNO_CARTAS_ESPECIAIS_HPP

#include "cartasNumericas.hpp"

class CartasEspeciais : public CartasNumericas{
    public:
        CartasEspeciais();
        bool pula_vez() override;
        bool come() override;
        bool inverte() override;
        //bool troca_cor() override;
};
#endif