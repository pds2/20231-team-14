#include "../../include/cartas/cartasNumericas.hpp"

CartasNumericas::CartasNumericas(){}

CartasNumericas::CartasNumericas(valor valor, cor cor){
    muda_valor(valor);
    muda_cor(cor);
}

bool CartasNumericas::verificar_jogada(Carta* carta){
    if(this->get_cor() <= cor(4)) {
        if(this->get_cor() != carta->get_cor() && this->get_valor() != carta->get_valor()) {
            return false;
        }
    }
    return true;
}