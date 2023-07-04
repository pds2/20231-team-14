#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include "../../include/baralho/monteCartasIniciais.hpp"

//Função auxiliar para gerar vetor com todas as cartas de um jogo completo
std::vector<Carta*> criar_monte_inicial() {
    std::vector<Carta*> vetor_temporario;
    /*
     * for(int i=0; i<108; i++) {
        CartasNumericas* nova_carta = new CartasNumericas(); 
        vetor_temporario.push_back(nova_carta);
    }
    */

    /*
    * Criando as cartas. Num jogo de uno, há 76 cartas numéricas (0 a 9, cada cor), 24 especiais
    * (block,+2 e inverter, cada cor) e 8 coringas (+4 e troca cor).
    */
    for (int i = 0; i < 76 ; i++){
        vetor_temporario.push_back(new CartasNumericas());
    }
    for(int i = 0; i < 24; i++){
        vetor_temporario.push_back(new CartasEspeciais());
    }
    for(int i = 0; i < 8; i++){
        vetor_temporario.push_back(new CartasEspeciaisPretas());
    }

    int count=0;
    //Adicionando um zero de cada cor
    for(int i=0; i<4; i++) {
        vetor_temporario[count]->muda_valor(0);
        vetor_temporario[count]->muda_cor(i);
        count++;
    }

    //Adicionando duas cartas *NÚMERICAS* de cada valor, com exceção do zero
    for(int i=0; i<2; i++) {
        for(int j=1; j<9; j++) {
            for(int k=0; k<4; k++) {
                vetor_temporario[count]->muda_valor(j);
                vetor_temporario[count]->muda_cor(k);
                count++;
            }
        }
    }
    
    //Adicionando duas cartas *ESPECIAIS* de cada valor
    for(int i=0; i<2; i++) {
        for(int j=9; j<13; j++) {
            for(int k=0; k<4; k++) {
                vetor_temporario[count]->muda_valor(j);
                vetor_temporario[count]->muda_cor(k);
                count++;
            }
        }
    }

    //Adicionando quatro cartas de cada carta preta
    for(int i=0; i<4; i++) {
        for(int j=13; j<15; j++) {
            vetor_temporario[count]->muda_valor(j);
            vetor_temporario[count]->muda_cor(4);
            count++;
        }
    }   

    return vetor_temporario;
}

MonteCartasIniciais::MonteCartasIniciais() : Baralho(108, criar_monte_inicial()) {};

std::vector<Carta*> MonteCartasIniciais::distribuir_mao_inicial(unsigned int qtd_cartas_iniciais) {
    std::vector<Carta*> vetor_temporario = get_cartas();
    std::vector<Carta*> mao;
    for(int i=0; i<(int)qtd_cartas_iniciais; i++) {
        mao.push_back(vetor_temporario[vetor_temporario.size()-1]);
        vetor_temporario.pop_back();
    }
    alterar_cartas(vetor_temporario);
    return mao;
}

Carta* MonteCartasIniciais::selecionar_carta_inicial() {
    std::vector<Carta*> vetor_temporario = get_cartas();
    unsigned int i = vetor_temporario.size()-1;
    while(vetor_temporario[i]->get_valor()==13) {
        i--;
    }
    Carta* carta_temporaria = vetor_temporario[i];
    vetor_temporario.erase(vetor_temporario.begin()+i);
    alterar_cartas(vetor_temporario);
    return carta_temporaria;
}