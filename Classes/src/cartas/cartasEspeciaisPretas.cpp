#include "../../include/cartas/cartasEspeciaisPretas.hpp"

CartasEspeciaisPretas::CartasEspeciaisPretas() : CartasEspeciais() {};

bool CartasEspeciaisPretas::come(){
    if (this->get_valor()==13) return true;
    else return false;
}

bool CartasEspeciaisPretas::trocar_cor(){
    if (this->get_valor()==14) return true;
    else return false;
}

bool CartasEspeciaisPretas::verificar_jogada(Carta* carta){
    return true;
}