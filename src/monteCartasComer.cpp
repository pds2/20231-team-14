#include "../include/monteCartasComer.hpp"

MonteCartasComer::MonteCartasComer(unsigned int numero_cartas_iniciais, int qtd_jogadores, 
                                    std::vector<Carta*> cartas_restantes) : Baralho(
                                    108-(numero_cartas_iniciais*qtd_jogadores)-1, cartas_restantes) {};

int MonteCartasComer::checar_reinicio() {
    if(get_numero_de_cartas()==0) {
        return 1;
    }
    return 0;
}

void MonteCartasComer::reiniciar_monte(std::vector<Carta*> cartas_restantes) {
    alterar_cartas(cartas_restantes);
    alterar_numero_cartas(cartas_restantes.size());
    embaralhar_cartas();
}

Carta* MonteCartasComer::comer_carta() {
    return retirar_carta_topo();
}