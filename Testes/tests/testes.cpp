#include "../third_party/doctest.h"

#include "../include/baralho.hpp"
#include "../include/bot.hpp"
#include "../include/cartas.hpp"
#include "../include/ciclo.hpp"
#include "../include/jogador.hpp"
#include "../include/maoJogador.hpp"
#include "../include/monteCartasComer.hpp"
#include "../include/monteCartasIniciais.hpp"
#include "../include/monteCartasJogadas.hpp"

TEST_CASE("01 - Testando as funções básicas de cartas: ") {
    CHECK_NOTHROW(Carta());
    CHECK_NOTHROW(Carta(valor(2), cor(3)));

    Carta carta_teste_1 = Carta(valor(6), cor(0));
    Carta carta_teste_2 = Carta(valor(8), cor(2));

    CHECK(carta_teste_1.get_cor() == cor(0));
    CHECK(carta_teste_2.get_valor() == valor(8));
    
    carta_teste_1.muda_valor(valor(5));
    CHECK(carta_teste_1.get_valor() == valor(5));

    carta_teste_2.muda_cor(cor(0));
    CHECK(carta_teste_1.get_cor() == cor(0));
}

TEST_CASE("02 - Testando as funções básicas do baralho: ") {
    CHECK_NOTHROW(Baralho());
    Carta* carta_1 = new Carta(valor(0), cor(0));
    Carta* carta_2 = new Carta(valor(1), cor(1));
    Carta* carta_3 = new Carta(valor(2), cor(2));
    std::vector<Carta*> cartas;
    cartas.push_back(carta_1);
    cartas.push_back(carta_2);

    Baralho* baralho_principal = new Baralho();
    baralho_principal->alterar_cartas(cartas);

    CHECK(baralho_principal->get_numero_de_cartas() == 2);
    CHECK(baralho_principal->get_cartas() == cartas);
    CHECK(baralho_principal->get_carta(0) == carta_1);

    cartas.push_back(carta_3);
    baralho_principal->alterar_cartas(cartas);
    CHECK(baralho_principal->get_numero_de_cartas() == 3);

    baralho_principal->limpar_cartas();
    CHECK(baralho_principal->get_numero_de_cartas() == 0);

    delete carta_1;
    delete carta_2;
    delete carta_3;
    delete baralho_principal;
}

TEST_CASE("03 - Testando as funções básicas do monte de cartas inicial:") {
    MonteCartasIniciais* monte_inicial = new MonteCartasIniciais();

    std::vector<Carta*> copia = monte_inicial->get_cartas();
    std::vector<Carta*> mao_inicial;

    int i = 4;
    int t = copia.size()-1;
    while(i--) {
        mao_inicial.push_back(copia[t]);
        copia.pop_back();
        t--;
    }

    CHECK(monte_inicial->distribuir_mao_inicial(4) == mao_inicial);
    Carta* inicial = monte_inicial->selecionar_carta_inicial();
    CHECK(monte_inicial->get_numero_de_cartas() == 103);

    delete inicial;
    for(Carta* c : mao_inicial) {
        delete c;
    }
    delete monte_inicial;
}

TEST_CASE("04 - Testando as funções básicas do monte de cartas para comer:") {
    MonteCartasIniciais* monte_inicial = new MonteCartasIniciais();
    std::vector<Carta*> mao_inicial = monte_inicial->distribuir_mao_inicial(4);
    MonteCartasComer* monte_compras = new MonteCartasComer(4, 1, monte_inicial->get_cartas());
    monte_inicial->limpar_cartas();

    Carta* compra = monte_compras->comer_carta();
    CHECK(monte_compras->get_numero_de_cartas() == 103);

    int i = 103;
    while(i--) {
        Carta* c = monte_compras->comer_carta();
        delete c;
    }
            
    CHECK(monte_compras->checar_reinicio() == true);

    Carta* carta_1 = new Carta(valor(0), cor(0));
    Carta* carta_2 = new Carta(valor(1), cor(1));
    std::vector<Carta*> cartas;
    cartas.push_back(carta_1);
    cartas.push_back(carta_2);

    monte_compras->reiniciar_monte(cartas);
    CHECK(monte_compras->get_numero_de_cartas() == 2);

    for(Carta *c : mao_inicial) {
        delete c;
    }
    delete compra;
    delete monte_compras;
    delete monte_inicial;
}

TEST_CASE("05 - Testando as funções básicas do monte de cartas jogadas:") {
    Carta* carta_1 = new Carta(valor(0), cor(0));
    Carta* carta_2 = new Carta(valor(1), cor(1 ));
    std::vector<Carta*> cartas;
    cartas.push_back(carta_1);

    MonteCartasJogadas* cartas_jogadas = new MonteCartasJogadas(cartas);

    CHECK(cartas_jogadas->mostrar_topo() == carta_1);

    cartas_jogadas->adicionar_carta_topo(carta_2);    
    CHECK(cartas_jogadas->mostrar_topo() == carta_2);

    delete cartas_jogadas;
}

TEST_CASE("06 - Testando as funcionalidades da mão do jogador:") {
    Carta* carta_1 = new Carta(valor(0), cor(0));
    Carta* carta_2 = new Carta(valor(1), cor(1));
    Carta* carta_3 = new Carta(valor(2), cor(2));
    std::vector<Carta*> cartas;
    cartas.push_back(carta_1);
    cartas.push_back(carta_2);

    MaoJogador* jogador = new MaoJogador(2, cartas);

    Carta* jogada = jogador->jogar_carta_selecionada(1);
    CHECK(jogador->get_numero_de_cartas() == 1);


    jogador->comprar_carta(carta_3);
    CHECK(jogador->get_numero_de_cartas() == 2);

    delete jogador;
    delete jogada;
}

TEST_CASE("07 - Testando as funcionalidades do ciclo:") {
    CHECK_NOTHROW(Ciclo());

    Ciclo* c = new Ciclo();
    for(int i = 0; i < 4; i++) {
        Jogador* novo_jogador = new Jogador(i);
        c->adicionar_jogadores(novo_jogador);
    }

    c->proximo_jogador();
    CHECK(c->get_index() == 1);
    CHECK(c->get_jogador_atual()->get_id() == 1);
    CHECK(c->get_proximo_jogador()->get_id() == 2);

    c->inverter();
    CHECK(c->get_proximo_jogador()->get_id() == 0);

    delete c;
}

TEST_CASE("08 - Testando as funcionalidades do jogador (com exclusão das jogadas):") {
    Jogador* jogador_um = new Jogador(1);
    CHECK(jogador_um->get_id() == 1);

    jogador_um->set_humano(true);
    CHECK(jogador_um->get_humano() == true);

    Carta* carta_1 = new Carta(valor(0), cor(0));
    Carta* carta_2 = new Carta(valor(1), cor(1));
    Carta* carta_3 = new Carta(valor(2), cor(2));
    std::vector<Carta*> cartas;
    cartas.push_back(carta_1);
    cartas.push_back(carta_2);
    cartas.push_back(carta_3);

    MaoJogador* mao = new MaoJogador(3, cartas);

    jogador_um->receber_cartas(mao);

    CHECK(jogador_um->get_mao() == mao);
    CHECK(jogador_um->get_mao()->get_numero_de_cartas() == 3);

    Carta* carta_topo_1 = new Carta(valor(0), cor(0));
    Carta* jogada_1 = jogador_um->jogar_carta(0, carta_topo_1);

    Carta* carta_topo_2 = new Carta(valor(1), cor(1));
    Carta* jogada_2 = jogador_um->jogar_carta(0, carta_topo_2);

    jogador_um->set_pedir_uno(true);
    CHECK(jogador_um->get_pediu_uno() == true);

    Carta* carta_topo_3 = new Carta(valor(2), cor(2));
    Carta* jogada_3 = jogador_um->jogar_carta(0, carta_topo_3);
    
    CHECK(jogador_um->verificar_vitoria() == true);

    delete jogada_1;
    delete jogada_2;
    delete jogada_3;
    delete carta_topo_1;
    delete carta_topo_2;
    delete carta_topo_3;
    delete jogador_um;
}

TEST_CASE("09 - Testando as funcionalidades de verificar/jogar cartas do jogador:") {
    CHECK_NOTHROW(Jogador(0));

    Jogador* jogador_um = new Jogador(1);

    Carta* carta_1 = new Carta(valor(0), cor(0));
    Carta* carta_2 = new Carta(valor(1), cor(1));
    std::vector<Carta*> cartas;
    cartas.push_back(carta_1);
    cartas.push_back(carta_2);

    MaoJogador* mao = new MaoJogador(2, cartas);
    jogador_um->receber_cartas(mao);

    Carta* carta_topo_1 = new Carta(valor(1), cor(1));
    CHECK(jogador_um->verifica_carta_jogada(1, carta_topo_1) == true);
    Carta* jogada_1 = jogador_um->jogar_carta(1, carta_topo_1);
    Carta* carta_topo_2 = new Carta(valor(14), cor(3));
    //Supondo que foi escolhida a cor vermelha no curinga
    CHECK(jogador_um->verifica_cor_jogada(0, cor(0)) == true);
    Carta* jogada_2 = jogador_um->jogar_carta_apenas_pela_cor(0, cor(0));

    delete jogada_1;
    delete jogada_2;
    delete carta_topo_1;
    delete carta_topo_2;
    delete jogador_um;
}

TEST_CASE("10 - Testando as funcionalidades de verificar/jogar cartas do bot:") {
    CHECK_NOTHROW(Bot(0));

    Bot* bot_um = new Bot(1);

    Carta* carta_1 = new Carta(valor(5), cor(0));
    Carta* carta_2 = new Carta(valor(8), cor(2));
    Carta* carta_3 = new Carta(valor(10), cor(3));
    std::vector<Carta*> cartas_bot;
    cartas_bot.push_back(carta_1);
    cartas_bot.push_back(carta_2);
    cartas_bot.push_back(carta_3);

    MaoJogador* mao_bot = new MaoJogador(3, cartas_bot);
    bot_um->receber_cartas(mao_bot);

    Carta* carta_topo_1 = new Carta(valor(1), cor(1));
    bot_um->jogar_carta(0, carta_topo_1);
    CHECK(bot_um->get_mao() == mao_bot);
    CHECK(bot_um->get_mao()->get_numero_de_cartas() == 3);

    Carta* carta_topo_2 = new Carta(valor(1), cor(2));
    Carta* jogada = bot_um->jogar_carta(0, carta_topo_2);
    CHECK(bot_um->get_mao()->get_numero_de_cartas() != 3);

    delete carta_topo_1;
    delete carta_topo_2;
    delete jogada;
    delete bot_um;
}