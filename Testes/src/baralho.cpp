#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "../include/baralho.hpp"

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

std::vector<Carta*> Baralho::get_cartas() {
    return _cartas;
}

Carta* Baralho::get_carta(unsigned int indice) {
    return _cartas[indice];
}   

void Baralho::imprimir_baralho() {
    unsigned int cout = 0;
    for(Carta* c : _cartas) {
        std::cout << cout << " - ";
        c->imprime_carta();    
        cout++;    
    }
    cout = 0;
}

void Baralho::alterar_numero_cartas(unsigned int novo_numero) {
    _numero_de_cartas = novo_numero;
}


void Baralho::alterar_cartas(std::vector<Carta*> novas_cartas) {
    _cartas.clear();
    _cartas = novas_cartas;
    _numero_de_cartas = novas_cartas.size();
}


void Baralho::embaralhar_cartas() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(_cartas.begin(), _cartas.end(), std::default_random_engine(seed));
}

void Baralho::limpar_cartas() {
    _numero_de_cartas = 0;

    std::vector<Carta*> vazio;
    _cartas = vazio;
}