#include "..\include\sistema.hpp"

#include <iostream>

Sistema::Sistema(){
    _partida_finalizada = false;
}

void Sistema::finalizar_partida(){
    _partida_finalizada = true;
}

void Sistema::nova_partida(int qntd_jogadores){
    Ciclo c = Ciclo();

    MonteCartasIniciais monte_inicial = MonteCartasIniciais();
    monte_inicial.embaralhar_cartas();

    int numero_cartas_iniciais = 7;
    //std::cout << "\nDigite o número de cartas: ";
    //std::cin >> numero_cartas_iniciais

    // Cria os jogadores e suas cartas
    for(int i = 1; i <= qntd_jogadores ; i++){
        std::vector<Carta*> mao_atual = monte_inicial.distribuir_mao_inicial(numero_cartas_iniciais);
        c.adicionar_jogadores(new Jogador(i));
        c.get_jogador(i)->receber_cartas(new MaoJogador(numero_cartas_iniciais, mao_atual));
    }

    std::cout << "\nIniciando partida!\n";
    double rodada = 1;

    std::vector<Carta*> inicio;
    inicio.push_back(monte_inicial.selecionar_carta_inicial());
    MonteCartasJogadas monte_principal = MonteCartasJogadas(inicio);
    
    MonteCartasComer monte_compras = MonteCartasComer(numero_cartas_iniciais, qntd_jogadores, monte_inicial.get_cartas());

    std::cout << "As cartas disponiveis para compra sao:" << std::endl;
    monte_compras.imprimir_baralho();
    std::cout << "\n-----------------------------------\n" << std::endl;

    std::cout << "A carta que comeca o jogo e:" << std::endl;
    monte_principal.imprimir_baralho();
    std::cout << "\n-----------------------------------\n" << std::endl;

    unsigned int indice_carta;
    while(!_partida_finalizada){
        std::cout << "\n-----------------------------------\n" << std::endl;
        std::cout << "\nRodada " << rodada << std::endl;
        std::cout << "\nVez do jogador " << c.get_jogador_atual()->get_id() << std::endl;
        std::cout << "Numero de cartas: " << c.get_jogador_atual()->get_mao()->get_numero_de_cartas();
        std::cout << "\nMao do jogador: \n\n";

        c.get_jogador_atual()->imprimir_mao();

        std::cout << "\n-----------------------------------\n"<< std::endl;
        std::cout << "Carta no topo: ";

        monte_principal.mostrar_topo()->imprime_carta();


        
        bool jogada_valida = false;
        /**
         * Esse if do indice carta = 99 é apenas para finalizar a partida/testar o código mais rápido
        */

        while(!jogada_valida){
            std::cout << "\n\nJogue uma carta: ";
            std::cin >> indice_carta;
            if (indice_carta >= 0  && indice_carta < c.get_jogador_atual()->get_mao()->get_numero_de_cartas()){
                jogada_valida = true;
            } else if (indice_carta == 99) {
                indice_carta = 0;
                jogada_valida = true;
                _partida_finalizada = true;
            }
            else {
                std::cout << "\nJogada inválida\n";
            }
        }

        /*
         *  Carta* carta = c.get_jogador_atual()->jogar_carta(indice_carta);
            monte_principal.adicionar_carta_topo(carta);       
            delete carta;
        */
        monte_principal.adicionar_carta_topo(c.get_jogador_atual()->jogar_carta(indice_carta));

        if (c.get_jogador_atual()->verificar_vitoria()) _partida_finalizada = true;
        else c.proximo_jogador();
        rodada++;
    }
    std::cout << "\n\nPartida finalizada!\n\n";
    std::cout << "Vencedor: Jogador " << c.get_index();
}