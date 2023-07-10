#include "../include/cartasEspeciais.hpp"

CartasEspeciais::CartasEspeciais(){};

bool CartasEspeciais::pula_vez(){
    if (this->get_valor() == valor(11)) return true;
    else return false;
}

bool CartasEspeciais::come(){
    if (this->get_valor() == valor(12)) return true;
    else return false;
}

bool CartasEspeciais::inverte(){
    if (this->get_valor() == valor(10)) return true;
    else return false;
}
// bool CartasEspeciais::troca_cor(){
//     return false;
// }