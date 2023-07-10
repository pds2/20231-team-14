#include "../include/cartasNumericas.hpp"

CartasNumericas::CartasNumericas(){}

CartasNumericas::CartasNumericas(valor valor, cor cor){
    muda_valor(valor);
    muda_cor(cor);
}

bool CartasNumericas::verificar_jogada(Carta* carta){
    if(this->get_cor() == carta->get_cor()) return true;
    else return false;
}

