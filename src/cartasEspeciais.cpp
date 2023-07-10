#include "../include/cartasEspeciais.hpp"

CartasEspeciais::CartasEspeciais(){};

bool CartasEspeciais::block(){
    if (this->get_valor()==11) return true;
    else return false;
}

bool CartasEspeciais::come(){
    if (this->get_valor()==12) return true;
    else return false;
}

bool CartasEspeciais::inverte(){
    if (this->get_valor()==10) return true;
    else return false;
}