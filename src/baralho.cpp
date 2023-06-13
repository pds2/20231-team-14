#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "../include/baralho.hpp"

Baralho::Baralho() {
    //Assumindo um jogo padrão de 108 cartas
    _numero_de_cartas = 108;

    std::vector<Carta*> vetor_temporario;
    for(int i=0; i<108; i++) {
        Carta* nova_carta = new Carta(); 
        vetor_temporario.push_back(nova_carta);
    }


    int count=0;
    //Adicionando um zero de cada cor
    for(int i=0; i<4; i++) {
        vetor_temporario[count]->muda_valor(0);
        vetor_temporario[count]->muda_cor(i);
        count++;
    }

    //Adicionando duas cartas de cada valor, com exceção do zero, mais quatro e curinga
    for(int i=0; i<2; i++) {
        for(int j=1; j<13; j++) {
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

    //Embaralhando todas as cartas
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (vetor_temporario.begin(), vetor_temporario.end(), std::default_random_engine(seed));

    for(int i=0; i<108; i++) {
        _cartas.push_back(vetor_temporario[i]);
    }
    
    vetor_temporario.clear();
}

Baralho::Baralho(std::vector<Carta*> x) {
    _numero_de_cartas = x.size();
    _cartas = x;
}

Baralho::~Baralho() {
    for(Carta* c : _cartas) {
        delete c;
    }
}

std::vector<Carta*> Baralho::get_cartas() {
    return _cartas;
}

void Baralho::imprimir_baralho() {
    for(Carta* c : _cartas) {
        c->imprime_carta();        
  }
}

Carta* Baralho::retirar_topo() {
    Carta* carta_temporaria = _cartas[_numero_de_cartas-1];
    _cartas.pop_back();
    return carta_temporaria;
}