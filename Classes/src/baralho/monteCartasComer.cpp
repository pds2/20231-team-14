#include "../../include/baralho/monteCartasComer.hpp"

MonteCartasComer::MonteCartasComer(unsigned int numero_cartas_iniciais, int qtd_jogadores, 
                                    std::vector<Carta*> cartas_restantes) : Baralho(
                                    108-(numero_cartas_iniciais*qtd_jogadores)-1, cartas_restantes) {};

MonteCartasComer::MonteCartasComer() : Baralho() {};

bool MonteCartasComer::checar_reinicio() {
    if(get_numero_de_cartas()==0) {
        return true;
    }
    return false;
}

void MonteCartasComer::reiniciar_monte(std::vector<Carta*> cartas_restantes) {
    alterar_cartas(cartas_restantes);
    alterar_numero_cartas(cartas_restantes.size());
    embaralhar_cartas();
}

Carta* MonteCartasComer::comer_carta() {
    if(get_numero_de_cartas()==0) {
        throw NumeroCartasInsuficientes_e();
    }

    std::vector<Carta*> vetor_temporario = get_cartas();
    int tam = vetor_temporario.size();
    Carta* ultima  = vetor_temporario[tam-1];
    vetor_temporario.pop_back();
    alterar_cartas(vetor_temporario);
    alterar_numero_cartas(vetor_temporario.size());
    return ultima;
}