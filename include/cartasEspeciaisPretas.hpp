#ifndef UNO_CARTAS_ESPECIAIS_PRETAS_HPP
#define UNO_CARTAS_ESPECIAIS_PRETAS_HPP

#include "cartasEspeciais.hpp"

class CartasEspeciaisPretas : public CartasEspeciais{
    public:
        CartasEspeciaisPretas();        
        bool come() override;
        bool troca_cor() override;
};

#endif