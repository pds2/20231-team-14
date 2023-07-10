#include "../../include/sistema/sistema.hpp"

Sistema::Sistema(int qntd_jogadores, int qntd_cartas_iniciais){
    this->qntd_jogadores = qntd_jogadores;
    this->qntd_cartas_iniciais = qntd_cartas_iniciais;

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

void Sistema::setar_curinga(){
    if(monte_principal->get_carta(monte_principal->get_numero_de_cartas()-1)->get_valor()!=14)
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
    monte_compras = new MonteCartasComer(qntd_cartas_iniciais, qntd_jogadores, monte_inicial->get_cartas());
    monte_inicial->limpar_cartas();
}

void Sistema::preparar_monte_cartas_jogadas(MonteCartasIniciais* monte_inicial){
    std::vector<Carta*> inicio;
    inicio.push_back(monte_inicial->selecionar_carta_inicial());
    monte_principal = new MonteCartasJogadas(inicio);
}

void Sistema::preparar_jogadores(MonteCartasIniciais* monte_inicial){
    for(int i = 0; i < qntd_jogadores; i++){
        std::vector<Carta*> mao_atual = monte_inicial->distribuir_mao_inicial(qntd_cartas_iniciais);
        if(i == 0){
            Jogador *jogador = new Jogador(i);
            c->adicionar_jogadores(jogador);
        }else{
            Bot *bot = new Bot(i);
            c->adicionar_jogadores(bot);
        }
        c->get_jogador(i)->receber_cartas(new MaoJogador(qntd_cartas_iniciais, mao_atual));
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
    int posicao_carta_mao = 0;
    while((carta_clicada->get_valor() != c->get_jogador_atual()->get_mao()->get_carta(posicao_carta_mao)->get_valor()) || \
    (carta_clicada->get_cor() != c->get_jogador_atual()->get_mao()->get_carta(posicao_carta_mao)->get_cor())){
        posicao_carta_mao++;
        if(posicao_carta_mao >= c->get_jogador_atual()->get_mao()->get_numero_de_cartas()) throw CartaNaoPertence_e {};
    }
    return posicao_carta_mao;
}

void Sistema::jogar_carta(int posicao_carta_mao){
    if(curinga==false) {
        Carta* carta_jogada = c->get_jogador_atual()->jogar_carta(posicao_carta_mao, monte_principal->mostrar_topo());
        monte_principal->adicionar_carta_topo(carta_jogada);
    }else{
        Carta* carta_jogada = c->get_jogador_atual()->jogar_carta_apenas_pela_cor(posicao_carta_mao, cor_atual);
        monte_principal->adicionar_carta_topo(carta_jogada);
    }      
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
            break;
        case valor(11):
            c->proximo_jogador();
            break;
        case valor(12):
            quantidade_cartas_comprar = 2;
            comprar_carta_proximo_jogador(quantidade_cartas_comprar);
            break;
        case valor(13): 
            quantidade_cartas_comprar = 4;
            comprar_carta_proximo_jogador(quantidade_cartas_comprar);
            break;
    }
    return quantidade_cartas_comprar;
}

void Sistema::comprar_carta_proximo_jogador(int quantidade_cartas){ 
    for(int i=0; i<quantidade_cartas; i++) {
        checar_reinicio_monte_compras();
        if(c->get_index() == qntd_jogadores-1) {
            c->get_jogador_por_indice(0)->get_mao()->comprar_carta(monte_compras->comer_carta());
        }else {
            c->get_proximo_jogador()->get_mao()->comprar_carta(monte_compras->comer_carta());
        } 
    }   
}

int Sistema::get_quantidade_jogadores(){
    return qntd_jogadores;
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

 Sistema::~Sistema(){
    //Destruir essas variaveis do heap está dando erro, tem que consertar porque deve estar tendo memory leak
    //delete c;
    //delete monte_principal;
    //delete monte_compras;
 }
