#ifndef UNO_CARTAS_ESPECIAIS_PRETAS_HPP
#define UNO_CARTAS_ESPECIAIS_PRETAS_HPP

#include "cartasEspeciais.hpp"

class CartasEspeciaisPretas : public CartasEspeciais{
    public:
        bool come() override;
        bool trocar_cor();
        bool verificar_jogada(Carta* carta) override;
};

#endif