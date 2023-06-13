#include <iostream>

#include "../include/jogador.hpp"

int main(){
    //Testando as funcioanalidades do baralho:
    Baralho baralho_teste = Baralho();

    baralho_teste.imprimir_baralho();

    std::cout << std::endl;

    Carta* carta_teste = baralho_teste.retirar_topo();  

    std::cout << "Carta retirada: ";

    carta_teste->imprime_carta();

    std::cout << std::endl;

    baralho_teste.imprimir_baralho();

    std::cout << std::endl;

    //Testando as funcioanalidades do jogador:
    Carta* um = new Carta(valor(1), cor(2));
    Carta* dois = new Carta(valor(2), cor(3));
    Carta* tres = new Carta(valor(3), cor(1));
    Carta* quatro = new Carta(valor(4), cor(2));

    std::vector<Carta*> mao;
    mao.push_back(um);
    mao.push_back(dois);
    mao.push_back(tres);
    mao.push_back(quatro);

    Jogador jogador_teste = Jogador(mao);

    std::cout << "A mão inicial do jogador é: " << std::endl;
    jogador_teste.imprimir_mao();

    std::cout << std::endl;

    Carta* carta_jogada = jogador_teste.jogar_carta(1);

    std::cout << "O jogador jogou: ";
    carta_jogada->imprime_carta();

    std::cout << std::endl;

    std::cout << "A mão do jogador agora é: " << std::endl;
    jogador_teste.imprimir_mao();

    return 0;
}

