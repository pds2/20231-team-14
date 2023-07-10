#include <iostream>
#include <map>
#include "../include/sistema.hpp"

int main(){
    int qntd_jogadores;
    
    std::cout << "\nDigite a quantidade de jogadores: ";
    std::cin >> qntd_jogadores;

    Sistema s = Sistema(qntd_jogadores,7);
    s.nova_partida();

}
