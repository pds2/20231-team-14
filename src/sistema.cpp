#include "../include/sistema.hpp"

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
    cor cor_atual = monte_inicial.get_carta(monte_inicial.get_numero_de_cartas()-1)->get_cor();

    bool curinga;
    if(monte_inicial.get_carta(monte_inicial.get_numero_de_cartas()-1)->get_valor()!=14) {
        curinga = false;
    }
    else {
        curinga = true;
    }

    while(!_partida_finalizada) {
        std::cout << "\n-----------------------------------\n" << std::endl;
        std::cout << "\nRodada " << rodada << std::endl;
        std::cout << "\nVez do jogador " << c.get_jogador_atual()->get_id() << std::endl;
        std::cout << "Numero de cartas: " << c.get_jogador_atual()->get_mao()->get_numero_de_cartas() << std::endl;
        std::cout << "Cor da vez: " << cor_atual << std::endl;
        std::cout << "\nMao do jogador: \n\n";

        c.get_jogador_atual()->imprimir_mao();

        std::cout << "\n-----------------------------------\n"<< std::endl;
        std::cout << "Carta no topo: ";
        monte_principal.mostrar_topo()->imprime_carta();
        std::cout << "\n-----------------------------------\n"<< std::endl;

        bool jogada = true;
        bool pular_vez = 0;
        while(jogada) {
            try {
                std::cout << "(1) Jogar carta" << std::endl;
                std::cout << "(2) Comprar carta" << std::endl << std::endl;

                int escolha;
                std::cin >> escolha;
                
                while(escolha == 2) {
                    std::vector<Carta*> vetor_temporario = c.get_jogador_atual()->get_mao()->get_cartas();
                    vetor_temporario.push_back(monte_compras.comer_carta());
                    c.get_jogador_atual()->get_mao()->alterar_cartas(vetor_temporario);
                    std::cout << std::endl;
                    std::cout << "Sua mão depois da compra é: " << std::endl;
                    c.get_jogador_atual()->imprimir_mao();
                    std::cout << "\n-----------------------------------\n"<< std::endl;
                    std::cout << "Carta no topo: ";
                    monte_principal.mostrar_topo()->imprime_carta();
                    std::cout << "\n-----------------------------------\n"<< std::endl << std::endl;
                    std::cout << "(1) Jogar carta" << std::endl;
                    std::cout << "(2) Comprar carta" << std::endl << std::endl;
                    std::cin >> escolha;
                    std::cout << std::endl;
                }

                std::cout << "Digite o índice da carta que você deseja jogar: ";
                std::cin >> indice_carta;
                std::cout << std::endl;
                if(curinga==false) {
                    monte_principal.adicionar_carta_topo(c.get_jogador_atual()->jogar_carta(indice_carta, monte_principal.mostrar_topo()));
                }
                else {
                    monte_principal.adicionar_carta_topo(c.get_jogador_atual()->jogar_carta_apenas_pela_cor(indice_carta, cor_atual));
                }
                
                valor checar_especial = monte_principal.mostrar_topo()->get_valor();
                switch(checar_especial) {
                    case valor(10):
                        c.inverter();
                        break;
                    case valor(11):
                        pular_vez = true;
                        break;
                    case valor(12):
                        for(int i=0; i<2; i++) {
                            if(c.get_index() == qntd_jogadores-1) {
                                c.get_jogador_por_indice(0)->get_mao()->comprar_carta(monte_compras.comer_carta());
                            }
                            else {
                                c.get_proximo_jogador()->get_mao()->comprar_carta(monte_compras.comer_carta());
                            }
                        }
                        break;
                    case valor(13): 
                        for(int i=0; i<4; i++) {
                            if(c.get_index() == qntd_jogadores -1) {
                                c.get_jogador_por_indice(0)->get_mao()->comprar_carta(monte_compras.comer_carta());
                            }
                            else {
                                c.get_proximo_jogador()->get_mao()->comprar_carta(monte_compras.comer_carta());
                            }
                        }
                        break;
                }

                cor checar_mudanca_de_cor = monte_principal.mostrar_topo()->get_cor();
                if(checar_mudanca_de_cor == cor(4)) {
                    std::cout << "(1) Vermelho " << std::endl;
                    std::cout << "(2) Verde " << std::endl;
                    std::cout << "(3) Azul " << std::endl;
                    std::cout << "(4) Amarelo " << std::endl << std::endl;
                    std::cout << "Escolha qual será a cor da vez: ";
                    int nova_cor;
                    std::cin >> nova_cor;
                    cor_atual = cor(nova_cor-1);
                    curinga = true;
                }
                else {
                    cor_atual = cor(monte_principal.mostrar_topo()->get_cor());
                    curinga = false;
                }

                jogada = false;
            } catch (JogadaInvalida_e &e) {
                std::cout << "Escolha uma carta válida!!!" << std::endl << std::endl;
            }
       }

        if (c.get_jogador_atual()->verificar_vitoria()) _partida_finalizada = true;
        c.proximo_jogador();
        if(pular_vez==true) c.proximo_jogador();

        rodada++;
    }

    std::cout << "\n\nPartida finalizada!\n\n";
    std::cout << "Vencedor: Jogador " << c.get_index();
}
       