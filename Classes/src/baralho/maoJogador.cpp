#include "../../include/baralho/maoJogador.hpp"
#include <iostream>
#include <string>

MaoJogador::MaoJogador(unsigned int qtd_cartas_inicial, 
                       std::vector<Carta*> mao_inicial) : Baralho(qtd_cartas_inicial, mao_inicial) {};

MaoJogador::MaoJogador(): Baralho() {}

Carta* MaoJogador::jogar_carta_selecionada(unsigned int indice) {
    if(indice >= get_numero_de_cartas()) {
        throw IndiceInvalido_e();
    }
    
    std::vector<Carta*> vetor_temporario = get_cartas();
    Carta* jogada_da_vez = vetor_temporario[indice];
    vetor_temporario.erase(vetor_temporario.begin()+indice);
    alterar_cartas(vetor_temporario);
    return jogada_da_vez;
}

void MaoJogador::comprar_carta(Carta* carta_comprada) {
    std::vector<Carta*> vetor_temporario = get_cartas();
    vetor_temporario.push_back(carta_comprada);
    alterar_cartas(vetor_temporario);
}

