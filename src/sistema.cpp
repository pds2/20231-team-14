#include "../include/sistema.hpp"

Sistema::Sistema(){
    cor_atual = cor(0);
}

Sistema::Sistema(int qntd_jogadores, int qntd_cartas_iniciais){
    _qntd_jogadores = qntd_jogadores;
    _qntd_cartas_iniciais = qntd_cartas_iniciais;

    if(qntd_jogadores < 0 || qntd_jogadores > 9 
       || qntd_cartas_iniciais <= 0|| qntd_cartas_iniciais > 108) {
        throw PartidaInvalida_e {};
    }

    c = new Ciclo();
    MonteCartasIniciais *monte_inicial = preparar_monte_inicial();
    preparar_jogadores(monte_inicial);
    preparar_monte_cartas_jogadas(monte_inicial);
    preparar_monte_cartas_para_compra(monte_inicial);

    cor_atual = monte_principal->get_carta(monte_principal->get_numero_de_cartas()-1)->get_cor();
    setar_curinga();

    delete monte_inicial;
}

void Sistema::nova_partida(){
    //Sistema sistema = Sistema(4,7);
    
    _qntd_jogadores = 3;
    _qntd_cartas_iniciais = 7;

    if(_qntd_jogadores < 0 || _qntd_jogadores > 9 
       || _qntd_cartas_iniciais <= 0|| _qntd_cartas_iniciais > 108) {
        throw PartidaInvalida_e {};
    }

    c = new Ciclo();
    MonteCartasIniciais *monte_inicial = preparar_monte_inicial();
    preparar_jogadores(monte_inicial);
    preparar_monte_cartas_jogadas(monte_inicial);
    preparar_monte_cartas_para_compra(monte_inicial);

    cor_atual = monte_principal->get_carta(monte_principal->get_numero_de_cartas()-1)->get_cor();
    setar_curinga();

    delete monte_inicial;

    std::cout << "\nIniciando partida!\n";
    double rodada = 1;

    std::cout << "As cartas disponiveis para compra sao:" << std::endl;
    monte_compras->imprimir_baralho();
    std::cout << "\n-----------------------------------\n" << std::endl;

    while(!_partida_finalizada){
        std::cout << "\n-----------------------------------\n" << std::endl;
        std::cout << "\nRodada " << rodada << std::endl;
        std::cout << "\nVez do jogador " << c->get_jogador_atual()->get_id() << std::endl;
        std::cout << "Numero de cartas: " << c->get_jogador_atual()->get_mao()->get_numero_de_cartas();
        if(c->get_jogador_atual()->get_humano()){
            std::cout << "\nJogador Humano\n";
            std::cout << "\nMao do jogador: \n\n";
            c->get_jogador_atual()->imprimir_mao();
            std::cout << "\n-----------------------------------\n"<< std::endl;
        }

        std::cout << "\nCarta no topo: ";
        monte_principal->mostrar_topo()->imprime_carta();
        std::cout << "\nCor: ";
        if(rodada == 1 ) cor_atual = monte_principal->mostrar_topo()->get_cor();
        //std::cout << cor(cor_atual) << std::endl; "0 - Vermelho ; 1 - Verde ; 2 - Azul ; 3 - Amarelo ; 4 - Preto"
        if(cor_atual == 0) std::cout << "Vermelho" << std::endl;
        else if(cor_atual == 1) std::cout << "Verde" << std::endl;
        else if(cor_atual == 2) std::cout << "Azul" << std::endl;
        else if(cor_atual == 3) std::cout << "Amarelo" << std::endl;
        else std::cout << "Preto" << std::endl;
        

        bool pode_jogar_carta = false;
        for(unsigned int i = 0; i < c->get_jogador_atual()->get_mao()->get_numero_de_cartas(); i++){
            if(c->get_jogador_atual()->verifica_carta_jogada(i,monte_principal->mostrar_topo()) || c->get_jogador_atual()->get_mao()->get_carta(i)->get_cor() == cor_atual || cor_atual == 4){
                pode_jogar_carta = true;
                std::cout << "\nO jogador tem cartas possiveis de ser jogadas!\n";
                std::cout << "-----------------------------------\n"<< std::endl;
                break;
            }
        }
        if(!pode_jogar_carta){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "\nO jogador nao tem uma carta valida!\n";
            std::cout << "-----------------------------------\n"<< std::endl;
            std::cout << "Comprando cartas carta\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            while(!pode_jogar_carta){
                comprar_carta();
                unsigned int ultima_carta = c->get_jogador_atual()->get_mao()->get_numero_de_cartas() - 1;

                if(c->get_jogador_atual()->get_humano()){
                    std::cout << "\nCarta comprada : " ;
                    c->get_jogador_atual()->get_mao()->get_carta(ultima_carta)->imprime_carta();
                }
                else {
                    std::cout << "\nComprando 1 carta.\n";
                }

                if(c->get_jogador_atual()->verifica_carta_jogada(ultima_carta,monte_principal->mostrar_topo())){
                    pode_jogar_carta = true;
                    if(c->get_jogador_atual()->get_humano()) {
                        std::cout << "\nO jogador pode jogar uma carta agora\n";
                        std::cout << "\nNumero de cartas: " << c->get_jogador_atual()->get_mao()->get_numero_de_cartas();
                        std::cout << "\nNova mao do jogador: \n\n";
                        c->get_jogador_atual()->imprimir_mao();

                        std::cout << "\n-----------------------------------\n"<< std::endl;
                        std::cout << "Carta no topo: ";
                        monte_principal->mostrar_topo()->imprime_carta();
                    }
                    else {
                        std::cout << "\nO jogador " << c->get_jogador_atual()->get_id() << " terminou de comprar cartas.\n";
                        std::cout << "\nNumero de cartas: " << c->get_jogador_atual()->get_mao()->get_numero_de_cartas();
                        std::cout << "\n-----------------------------------\n"<< std::endl;
                        std::cout << "Carta no topo: ";
                        monte_principal->mostrar_topo()->imprime_carta();
                    }

                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            
        }

        unsigned int indice_carta;
        bool jogada_valida = false;
        if(pode_jogar_carta){
                while(!jogada_valida){
                    if(!c->get_jogador_atual()->get_humano()){
                        indice_carta = 0;
                        std::cout << "\nCarta no topo: ";
                        monte_principal->mostrar_topo()->imprime_carta();
                        std::cout << "\nEscolhendo uma carta...\n";
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        monte_principal->adicionar_carta_topo(c->get_jogador_atual()->jogar_carta(indice_carta, monte_principal->mostrar_topo()));                
                        cor_atual = monte_principal->mostrar_topo()->get_cor();
                        std::cout << "\n-----------------------------------\n"<< std::endl;
                        std::cout << "\nCarta jogada : ";
                        monte_principal->mostrar_topo()->imprime_carta();
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        jogada_valida = true;
                    }
                    else{
                        std::cout << "\n\nJogue uma carta: ";
                        std::cin >> indice_carta;
                        if (indice_carta >= 0  && indice_carta < c->get_jogador_atual()->get_mao()->get_numero_de_cartas()){
                            jogada_valida = true;
                        } 
                        else if (indice_carta == 99) {
                            indice_carta = 0;
                            jogada_valida = true;
                            _partida_finalizada = true;
                        }
                        else {
                            std::cout << "\nIndice invalido\n";
                        }
                        if(c->get_jogador_atual()->verifica_carta_jogada(indice_carta, monte_principal->mostrar_topo()) || c->get_jogador_atual()->get_mao()->get_carta(indice_carta)->get_cor() == cor_atual){
                            cor_atual = c->get_jogador_atual()->get_mao()->get_carta(indice_carta)->get_cor();
                            monte_principal->adicionar_carta_topo(c->get_jogador_atual()->jogar_carta(indice_carta, monte_principal->mostrar_topo()));
                        }
                        else {
                            if(indice_carta == 99) {
                                jogada_valida = true;
                            }
                            jogada_valida = false;
                            std::cout << "\nJogada nao eh possivel\n";
                        }
                    }      
            }
        }

        if (c->get_jogador_atual()->verificar_vitoria()) _partida_finalizada = true;
        else {
            if(checa_mudanca_cor()){
                unsigned short cor_desejada;
                if(!c->get_jogador_atual()->get_humano()){
                    std::cout << "\nCoringa jogado!\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::srand(std::time(0));
                    cor_desejada = std::rand() % 4; // Gera um número aleatório entre 0 e 3
                }
                else {
                    std::cout << "\nCoringa jogado!\n"; 
                    std::cout << "\nDigite a cor desejada!\n";
                    std::cout << "0 - Vermelho ; 1 - Verde ; 2 - Azul ; 3 - Amarelo\n";
                    std::cin >> cor_desejada;
                }
                
                switch(cor_desejada){
                    case 0: 
                        cor_atual = cor(0);
                        monte_principal->mostrar_topo()->muda_cor(cor_atual);
                        std::cout << "\nCor escolhida : Vermelho\n";
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        break;
                    case 1:
                        cor_atual = cor(1);
                        monte_principal->mostrar_topo()->muda_cor(cor_atual);
                        std::cout << "\nCor escolhida : Verde\n";
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        break;
                    case 2:
                        cor_atual = cor(2);
                        monte_principal->mostrar_topo()->muda_cor(cor_atual);
                        std::cout << "\nCor escolhida : Azul\n";
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        break;
                    case 3:
                        cor_atual = cor(3);
                        monte_principal->mostrar_topo()->muda_cor(cor_atual);
                        std::cout << "\nCor escolhida : Amarelo\n";
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        break;
                    default:
                        std::cout << "\nCor invalida\n";
                        std::cout << "\nCor escolhida default : Vermelho\n";
                        cor_atual = cor(0);
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        break;
                }

            }
            aplicar_efeito_especial();
            c->proximo_jogador();
        }
        rodada++;
    }
    std::cout << "\n\nPartida finalizada!\n\n";
    std::cout << "Vencedor: Jogador " << c->get_index();
}

void Sistema::setar_curinga(){
    if(monte_principal->get_carta(monte_principal->get_numero_de_cartas()-1)->get_valor() < 13)
        curinga = false;
    else 
        curinga = true;
}

MonteCartasIniciais* Sistema::preparar_monte_inicial(){
    MonteCartasIniciais* monte_inicial = new MonteCartasIniciais();
    monte_inicial->embaralhar_cartas();
    return monte_inicial;
}

void Sistema::preparar_monte_cartas_para_compra(MonteCartasIniciais* monte_inicial){
    monte_compras = new MonteCartasComer(_qntd_cartas_iniciais, _qntd_jogadores, monte_inicial->get_cartas());
    monte_inicial->limpar_cartas();
}

void Sistema::preparar_monte_cartas_jogadas(MonteCartasIniciais* monte_inicial){
    std::vector<Carta*> inicio;
    inicio.push_back(monte_inicial->selecionar_carta_inicial());
    monte_principal = new MonteCartasJogadas(inicio);
}

void Sistema::preparar_jogadores(MonteCartasIniciais* monte_inicial){
    for(int i = 1; i < _qntd_jogadores+1; i++){
        std::vector<Carta*> mao_atual = monte_inicial->distribuir_mao_inicial(_qntd_cartas_iniciais);
        if(i == 1){
            Jogador *jogador = new Jogador(i);
            c->adicionar_jogadores(jogador);
            c->get_jogador(i)->receber_cartas(new MaoJogador(_qntd_cartas_iniciais, mao_atual));
        }
        else {
            Bot *jogador = new Bot(i);
            c->adicionar_jogadores(jogador);
            c->get_jogador(i)->receber_cartas(new MaoJogador(_qntd_cartas_iniciais, mao_atual));
        }
        
    }
}

void Sistema::comprar_carta(){
    checar_reinicio_monte_compras();
    c->get_jogador_atual()->get_mao()->comprar_carta(monte_compras->comer_carta()); 
}

void Sistema::checar_reinicio_monte_compras(){
    if(monte_compras->checar_reinicio()){
        std::vector<Carta*> vetor_temporario_1 = monte_principal->get_cartas();
        vetor_temporario_1.pop_back();
        monte_compras->reiniciar_monte(vetor_temporario_1);

        Carta* carta_topo = monte_principal->get_carta(monte_principal->get_numero_de_cartas()-1);
        std::vector<Carta*> vetor_temporario_2;
        vetor_temporario_2.push_back(carta_topo);
        monte_principal->alterar_cartas(vetor_temporario_2);
    }
}

int Sistema::definir_indice_carta_jogada(Carta *carta_clicada){
    unsigned int posicao_carta_mao = 0;
    while((carta_clicada->get_valor() != c->get_jogador_atual()->get_mao()->get_carta(posicao_carta_mao)->get_valor()) || \
    (carta_clicada->get_cor() != c->get_jogador_atual()->get_mao()->get_carta(posicao_carta_mao)->get_cor())){
        posicao_carta_mao++;
        if(posicao_carta_mao >= c->get_jogador_atual()->get_mao()->get_numero_de_cartas()) throw CartaNaoPertence_e {};
    }
    return posicao_carta_mao;
}

bool Sistema::jogar_carta(int posicao_carta_mao){
    if(curinga==false) {
        if(c->get_jogador_atual()->verifica_carta_jogada(posicao_carta_mao, monte_principal->mostrar_topo())){
            monte_principal->adicionar_carta_topo(c->get_jogador_atual()->jogar_carta(posicao_carta_mao, monte_principal->mostrar_topo()));
            return true;
        }
    }else{
        if(c->get_jogador_atual()->verifica_cor_jogada(posicao_carta_mao, cor_atual)){
            monte_principal->adicionar_carta_topo(c->get_jogador_atual()->jogar_carta_apenas_pela_cor(posicao_carta_mao, cor_atual));
            return true;
        }
    }  
    return false;      
}

bool Sistema::checa_mudanca_cor(){
    cor checar_mudanca_de_cor = monte_principal->mostrar_topo()->get_cor();
    if(checar_mudanca_de_cor == cor(4)) {
        curinga = true;
        return true;
    }
    curinga = false;
    return false; 
}

int Sistema::aplicar_efeito_especial(){    
    int quantidade_cartas_comprar = 0;
    valor checar_especial = monte_principal->mostrar_topo()->get_valor();
    switch(checar_especial) {
        case valor(10):
            c->inverter();
            std::cout << "\nInvertendo ordem dos jogadores.\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        case valor(11):
            std::cout << "\nJogador " << c->get_proximo_jogador()->get_id() << " teve sua vez pulada...\n";
            c->proximo_jogador();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        case valor(12):
            quantidade_cartas_comprar = 2;
            comprar_carta_proximo_jogador(quantidade_cartas_comprar);
            std::cout << "\nJogador " << c->get_proximo_jogador()->get_id() << " comeu 2 cartas...\n";
            std::cout << "E teve sua vez pulada.\n";
            c->proximo_jogador();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        case valor(13): 
            quantidade_cartas_comprar = 4;
            comprar_carta_proximo_jogador(quantidade_cartas_comprar);
            std::cout << "\nJogador " << c->get_proximo_jogador()->get_id() << " comeu 4 cartas...\n";
            std::cout << "E teve sua vez pulada.\n";
            c->proximo_jogador();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        default:
            break;
    }
    return quantidade_cartas_comprar;
}

void Sistema::comprar_carta_proximo_jogador(int quantidade_cartas){ 
    for(int i=0; i<quantidade_cartas; i++) {
        checar_reinicio_monte_compras();
        if(c->get_index() >= _qntd_jogadores-1) {
            c->get_jogador_por_indice(0)->get_mao()->comprar_carta(monte_compras->comer_carta());
        }else {
            c->get_proximo_jogador()->get_mao()->comprar_carta(monte_compras->comer_carta());
        } 
    }   
}

int Sistema::get_quantidade_jogadores(){
    return _qntd_jogadores;
}

Ciclo* Sistema::get_ciclo(){
    return c;
}

MonteCartasComer* Sistema::get_monte_compras(){
    return monte_compras;
}

MonteCartasJogadas* Sistema::get_monte_jogadas(){
    return monte_principal;
}

 void Sistema::set_cor_atual(cor cor_atual){
    this->cor_atual = cor_atual;
 }

 cor Sistema::get_cor_atual(){
    return cor_atual;
 }

 Sistema::~Sistema(){
    delete c;
    delete monte_principal;
    delete monte_compras;
 }
