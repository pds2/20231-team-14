#include "../../include/baralho/monteCartasJogadas.hpp"

MonteCartasJogadas::MonteCartasJogadas(std::vector<Carta*> carta_inicial) : Baralho(1,carta_inicial) {};

MonteCartasJogadas::MonteCartasJogadas() : Baralho() {};

Carta* MonteCartasJogadas::mostrar_topo() {
    std::vector<Carta*> vetor_temporario = get_cartas();
    return vetor_temporario[vetor_temporario.size()-1];
}

void MonteCartasJogadas::adicionar_carta_topo(Carta* carta_jogada) {
    std::vector<Carta*> vetor_temporario = get_cartas();
    vetor_temporario.push_back(carta_jogada);
    alterar_cartas(vetor_temporario);
}