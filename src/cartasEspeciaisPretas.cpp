#include "../include/cartasEspeciaisPretas.hpp"

CartasEspeciaisPretas::CartasEspeciaisPretas(){};

bool CartasEspeciaisPretas::come(){
    if (this->get_valor()==valor(13)) return true;
    else return false;
}

bool CartasEspeciaisPretas::troca_cor(){
    return true;
}
