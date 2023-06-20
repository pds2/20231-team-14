#include <iostream>
#include <map>
#include "../include/monteCartasIniciais.hpp"
#include "../include/monteCartasComer.hpp"
#include "../include/monteCartasJogadas.hpp"
#include "../include/maoJogador.hpp"

std::vector<Carta*> criar_baralho() {
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

    //Adicionando duas cartas de cada valor, com exceção de: zero, mais quatro e curinga
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

    return vetor_temporario;
}

//Apenas para testes
int main(){
    MonteCartasIniciais monte_inicial = MonteCartasIniciais();
    monte_inicial.embaralhar_cartas();

    int numero_jogadores, numero_cartas_iniciais;
    std::cout << "Insira o numero de jogadores: ";
    std::cin >> numero_jogadores;
    std::cout << "Insira o numero de cartas iniciais: ";
    std::cin >> numero_cartas_iniciais;

    std::cout << std::endl;
    std::cout << "O monte inicial é: " << std::endl;
    monte_inicial.imprimir_baralho();
    std::cout << std::endl;

    for(int i=0; i<numero_jogadores; i++) {
        std::vector<Carta*> mao_atual = monte_inicial.distribuir_mao_inicial(numero_cartas_iniciais);
        MaoJogador mao_jogador_atual = MaoJogador(numero_cartas_iniciais, mao_atual);
        std::cout << "A mao do jogador " << i+1 << " e:" << std::endl;
        mao_jogador_atual.imprimir_baralho();
        std::cout << std::endl;
    }

    std::vector<Carta*> inicio;
    inicio.push_back(monte_inicial.selecionar_carta_inicial());
    MonteCartasJogadas monte_principal = MonteCartasJogadas(inicio);
    
    std::cout << "A carta que comeca o jogo e:" << std::endl;
    monte_principal.imprimir_baralho();
    std::cout << std::endl;

    MonteCartasComer monte_compras = MonteCartasComer(numero_cartas_iniciais, 
                                                      numero_jogadores, monte_inicial.get_cartas());

    std::cout << "As cartas disponiveis para compra sao:" << std::endl;
    monte_compras.imprimir_baralho();

    monte_inicial.limpar_cartas();
}

