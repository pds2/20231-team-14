#include "../include/sistema.hpp"

#include <iostream>

void setar_curinga(MonteCartasJogadas* monte_principal, bool& curinga) {
    if(monte_principal->get_carta(monte_principal->get_numero_de_cartas()-1)->get_valor()!=14)
        curinga = false;
    else 
        curinga = true;
}

Sistema::Sistema(){
    _partida_finalizada = false;
}

void Sistema::finalizar_partida(){
    _partida_finalizada = true;
}

MonteCartasIniciais* Sistema::preparar_monte_inicial() {
    MonteCartasIniciais* monte_inicial = new MonteCartasIniciais();
    monte_inicial->embaralhar_cartas();
    return monte_inicial;
}

MonteCartasJogadas* Sistema::preparar_monte_cartas_jogadas(MonteCartasIniciais* monte_inicial) {
    std::vector<Carta*> inicio;
    inicio.push_back(monte_inicial->selecionar_carta_inicial());
    MonteCartasJogadas* monte_principal = new MonteCartasJogadas(inicio);
    return monte_principal;
}

MonteCartasComer* Sistema::preparar_monte_cartas_para_compra(MonteCartasIniciais* monte_inicial, int qntd_cartas_iniciais, int qntd_jogadores) {
    MonteCartasComer* monte_compras = new MonteCartasComer(qntd_cartas_iniciais, qntd_jogadores, monte_inicial->get_cartas());
    monte_inicial->limpar_cartas();
    return monte_compras;
}

void Sistema::preparar_jogadores(Ciclo* c, MonteCartasIniciais* monte_inicial, int qntd_jogadores, int qntd_cartas_iniciais) {
    for(int i = 0; i < qntd_jogadores; i++){
        std::vector<Carta*> mao_atual = monte_inicial->distribuir_mao_inicial(qntd_cartas_iniciais);
        c->adicionar_jogadores(new Jogador(i));
        c->get_jogador(i)->receber_cartas(new MaoJogador(qntd_cartas_iniciais, mao_atual));
    }
}

void Sistema::imprimir_informacoes_inicio_partida(MonteCartasJogadas* monte_principal) {
    std::cout << "\nIniciando partida!\n\n";
    std::cout << "A carta que comeca o jogo e:" << std::endl;
    monte_principal->imprimir_baralho();
    std::cout << "-----------------------------------\n" << std::endl;
}

void Sistema::imprimir_informacoes_inicio_rodada(Ciclo* c, MonteCartasJogadas* monte_principal, int rodada, cor cor_atual) {
    std::cout << "\n-----------------------------------\n" << std::endl;
        std::cout << "\nRodada " << rodada << std::endl;
        std::cout << "\nVez do jogador " << c->get_jogador_atual()->get_id() << std::endl;
        std::cout << "Numero de cartas: " << c->get_jogador_atual()->get_mao()->get_numero_de_cartas() << std::endl;
        std::cout << "Cor da vez: " << cor_atual << std::endl;
        std::cout << "\nMao do jogador: \n\n";
        c->get_jogador_atual()->imprimir_mao();
        std::cout << "\n-----------------------------------\n"<< std::endl;
        std::cout << "Carta no topo: ";
        monte_principal->mostrar_topo()->imprime_carta();
        std::cout << "\n-----------------------------------\n"<< std::endl;
}

void Sistema::comprar_e_imprimir_informacoes(Ciclo* c, MonteCartasComer* monte_compras, MonteCartasJogadas* monte_principal) {
    std::vector<Carta*> vetor_temporario = c->get_jogador_atual()->get_mao()->get_cartas();
    vetor_temporario.push_back(monte_compras->comer_carta());
    c->get_jogador_atual()->get_mao()->alterar_cartas(vetor_temporario);
    std::cout << std::endl;
    std::cout << "Sua mão depois da compra é: " << std::endl;
    c->get_jogador_atual()->imprimir_mao();
    std::cout << "\n-----------------------------------\n"<< std::endl;
    std::cout << "Carta no topo: ";
    monte_principal->mostrar_topo()->imprime_carta();
    std::cout << "\n-----------------------------------\n"<< std::endl << std::endl;
    std::cout << "(1) Jogar carta" << std::endl;
    std::cout << "(2) Comprar carta" << std::endl << std::endl;
}

void Sistema::fazer_jogada(Ciclo* c, MonteCartasJogadas* monte_principal, bool& curinga, int indice_carta, cor& cor_atual) {
    if(curinga==false) {
        monte_principal->adicionar_carta_topo(c->get_jogador_atual()->jogar_carta(indice_carta, monte_principal->mostrar_topo()));
    }
    else {
        monte_principal->adicionar_carta_topo(c->get_jogador_atual()->jogar_carta_apenas_pela_cor(indice_carta, cor_atual));
    }
}

void Sistema::checar_reinicio_monte_compras(MonteCartasComer* monte_compras, MonteCartasJogadas* monte_principal) {
    if(monte_compras->checar_reinicio()) {
                        std::vector<Carta*> vetor_temporario_1 = monte_principal->get_cartas();
                        vetor_temporario_1.pop_back();
                        monte_compras->reiniciar_monte(vetor_temporario_1);

                        Carta* carta_topo = monte_principal->get_carta(monte_principal->get_numero_de_cartas()-1);
                        std::vector<Carta*> vetor_temporario_2;
                        vetor_temporario_2.push_back(carta_topo);
                        monte_principal->alterar_cartas(vetor_temporario_2);
                    }
}

void Sistema::aplicar_efeito_especial(Ciclo* c, MonteCartasComer* monte_compras, bool& pular_vez, int qntd_jogadores, valor checar_especial) {
    switch(checar_especial) {
        case valor(10):
            c->inverter();
            break;
        case valor(11):
            pular_vez = true;
            break;
        case valor(12):
            for(int i=0; i<2; i++) {
                if(c->get_index() == qntd_jogadores-1) {
                    c->get_jogador_por_indice(0)->get_mao()->comprar_carta(monte_compras->comer_carta());
                }
                else {
                    c->get_proximo_jogador()->get_mao()->comprar_carta(monte_compras->comer_carta());
                }
            }
            break;
        case valor(13): 
            for(int i=0; i<4; i++) {
                if(c->get_index() == qntd_jogadores -1) {
                    c->get_jogador_por_indice(0)->get_mao()->comprar_carta(monte_compras->comer_carta());
                }
                else {
                    c->get_proximo_jogador()->get_mao()->comprar_carta(monte_compras->comer_carta());
                }
            }
            break;
    }
}

void Sistema::aplicar_mudanca_cor(MonteCartasJogadas* monte_principal, bool& curinga, cor checar_mudanca_de_cor, cor& cor_atual) {
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
        cor_atual = cor(monte_principal->mostrar_topo()->get_cor());
        curinga = false;
    }
}

void Sistema::nova_partida(int qntd_jogadores, int qntd_cartas_iniciais){
    if(qntd_jogadores < 0 || qntd_jogadores > 9 
       || qntd_cartas_iniciais <= 0|| qntd_cartas_iniciais > 108) {
        throw PartidaInvalida_e {};
    }

    //Preparando os jogadores e os baralhos em um ciclo na partida, imprimindo as informações
    Ciclo* c = new Ciclo();
    MonteCartasIniciais* monte_inicial = this->preparar_monte_inicial();
    this->preparar_jogadores(c, monte_inicial, qntd_jogadores, qntd_cartas_iniciais);
    MonteCartasJogadas* monte_principal = this->preparar_monte_cartas_jogadas(monte_inicial);
    MonteCartasComer* monte_compras = this->preparar_monte_cartas_para_compra(monte_inicial, qntd_cartas_iniciais, qntd_jogadores);
    this->imprimir_informacoes_inicio_partida(monte_principal);

    int rodada = 1;
    unsigned int indice_carta;
    bool curinga;

    cor cor_atual = monte_principal->get_carta(monte_principal->get_numero_de_cartas()-1)->get_cor();
    setar_curinga(monte_principal, curinga);

    while(!_partida_finalizada) {
        bool jogada = true;
        bool pular_vez = false;

        this->imprimir_informacoes_inicio_rodada(c, monte_principal, rodada, cor_atual);

        while(jogada) {
            try {
                std::cout << "(1) Jogar carta" << std::endl;
                std::cout << "(2) Comprar carta" << std::endl << std::endl;
                int escolha;
                std::cin >> escolha;
                
                while(escolha == 2) {
                    this->checar_reinicio_monte_compras(monte_compras, monte_principal);
                    this->comprar_e_imprimir_informacoes(c, monte_compras, monte_principal);
                    std::cin >> escolha;
                    std::cout << std::endl;
                }

                std::cout << "Digite o índice da carta que você deseja jogar: ";
                std::cin >> indice_carta;
                std::cout << std::endl;

                this->fazer_jogada(c, monte_principal, curinga, indice_carta, cor_atual);
                valor checar_especial = monte_principal->mostrar_topo()->get_valor();
                this->aplicar_efeito_especial(c, monte_compras, pular_vez, qntd_jogadores, checar_especial);
                cor checar_mudanca_de_cor = monte_principal->mostrar_topo()->get_cor();
                this->aplicar_mudanca_cor(monte_principal, curinga, checar_mudanca_de_cor, cor_atual);

                jogada = false;
            } catch (JogadaInvalida_e &e) {
                std::cout << "Escolha uma carta válida!!!" << std::endl << std::endl;
            }
       }
        if (c->get_jogador_atual()->verificar_vitoria()) _partida_finalizada = true;
        c->proximo_jogador();
        if(pular_vez==true) c->proximo_jogador();    
        rodada++;
    }
    std::cout << "\n\nPartida finalizada!\n\n";
    std::cout << "Vencedor: Jogador " << c->get_index();
}
       