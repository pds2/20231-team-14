#include <iostream>
#include <map>
#include "../include/monteCartasIniciais.hpp"
#include "../include/monteCartasComer.hpp"
#include "../include/monteCartasJogadas.hpp"
#include "../include/maoJogador.hpp"
#include "../include/ciclo.hpp"
#include "../include/jogador.hpp"
#include "../include/sistema.hpp"

int main(){
    int qntd_jogadores;
    Sistema s = Sistema();
    std::cout << "\nDigite a quantidade de jogadores: ";
    std::cin >> qntd_jogadores;
    s.nova_partida(qntd_jogadores);
}
