#include <iostream>
#include "../../include/cartas/cartas.hpp"

Carta::Carta() {}

Carta::Carta(valor valor, cor cor) {
    _valor = valor;
    _cor = cor;
}

valor Carta::get_valor() {
    return _valor;
}

cor Carta::get_cor() {
    return _cor;
}

void Carta::imprime_carta() {
    switch(_valor) {
            case 0:
                std::cout << "0 ";
                break;
            case 1:
                std::cout << "1 ";
                break;
            case 2:
                std::cout << "2 ";
                break;
            case 3:
                std::cout << "3 ";
                break;
            case 4:
                std::cout << "4 ";
                break;
            case 5:
                std::cout << "5 ";
                break;
            case 6:
                std::cout << "6 ";
                break;
            case 7:
                std::cout << "7 ";
                break;
            case 8:
                std::cout << "8 ";
                break;
            case 9: 
                std::cout << "9 ";
                break;
            case 10: 
                std::cout << "Inverte ordem ";
                break;
            case 11: 
                std::cout << "Pula vez ";
                break;
            case 12: 
                std::cout << "Mais dois ";
                break;
            case 13: 
                std::cout << "Mais quatro ";
                break;
            case 14: 
                std::cout << "Curinga ";
                break;
    }
    switch (_cor) {
            case 0:
                std::cout << "Vermelho";
                break;
            case 1:
                std::cout << "Verde";
                break;
            case 2:
                std::cout << "Azul";
                break;
            case 3:
                std::cout << "Amarelo";
                break;
            case 4:
                std::cout << "Preto";
                break;
        }
        std::cout << std::endl;
}

void Carta::muda_valor(unsigned int val) {
    if(val >= 15) {
        throw ValorInvalido_e();
    }
    _valor = valor(val);
}

void Carta::muda_cor(unsigned int c) {
    if(c > 4) {
        throw CorInvalida_e();
    }
    _cor = cor(c);
}

std::string Carta::get_sprite(){
    return (std::to_string(_valor) + "_" + std::to_string(_cor) + ".png");
}