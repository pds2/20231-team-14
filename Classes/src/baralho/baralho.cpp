#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "../../include/baralho/baralho.hpp"

Baralho::Baralho() {
    _numero_de_cartas = 0;
    std::vector<Carta*> vazio;
    _cartas = vazio;
}

Baralho::Baralho(unsigned int numero_de_cartas, std::vector<Carta*> cartas) {
    _numero_de_cartas = numero_de_cartas;
    _cartas = cartas;
}

Baralho::~Baralho() {
    for(Carta* c : _cartas) {
        delete c;
    }
}

unsigned int Baralho::get_numero_de_cartas() {
    return _numero_de_cartas;
}

void Baralho::alterar_numero_cartas(unsigned int novo_numero) {
    _numero_de_cartas = novo_numero;
}

std::vector<Carta*> Baralho::get_cartas() {
    return _cartas;
}

Carta* Baralho::get_carta(unsigned int indice) {
    return _cartas[indice];
}   

void Baralho::alterar_cartas(std::vector<Carta*> novas_cartas) {
    _cartas.clear();
    _cartas = novas_cartas;
    _numero_de_cartas = novas_cartas.size();
}

void Baralho::imprimir_baralho() {
    for(Carta* c : _cartas) {
        c->imprime_carta();        
  }
}

void Baralho::embaralhar_cartas() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(_cartas.begin(), _cartas.end(), std::default_random_engine(seed));
}

Carta* Baralho::retirar_carta_topo() {
    std::vector<Carta*> vetor_temporario = get_cartas();
    int tam = vetor_temporario.size();
    Carta* ultima  = vetor_temporario[tam-1];
    vetor_temporario.erase(vetor_temporario.begin()+tam-1);
    alterar_cartas(vetor_temporario);
    _numero_de_cartas=vetor_temporario.size();
    return ultima;
}

void Baralho::limpar_cartas() {
    _numero_de_cartas = 0;

    std::vector<Carta*> vazio;
    _cartas = vazio;
}