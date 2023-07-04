#include "../../include/interface/interface.hpp"


cocos2d::Scene* Interface::createScene(){
    cocos2d::Scene* scene = cocos2d::Scene::create();
    cocos2d::Layer* layer = Interface::create();
    scene->addChild(layer);
    
    return scene;
}

bool Interface::init(){
    if ( !cocos2d::Layer::init() )
    {
        return false;
    }
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    spritescartas = cocos2d::SpriteFrameCache::getInstance();
    spritescartas->addSpriteFramesWithFile("cartasUno.plist");
    _partida_finalizada = false;
    criaPartida();

    return true;
}

void Interface::finalizarPartida(){
    _partida_finalizada = true;
}

void Interface::criaPartida(){
    int qntd_jogadores = 4;
    c = Ciclo();

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
    monte_principal.alterar_cartas(inicio);
    monte_principal.alterar_numero_cartas(1);
    criaMonte();

    
    monte_compras.alterar_cartas(monte_inicial.get_cartas());
    monte_compras.alterar_numero_cartas((108-(numero_cartas_iniciais*qntd_jogadores)-1));
    criaBaralho();

    criaJogador();

    std::cout << "As cartas disponiveis para compra sao:" << std::endl;
    monte_compras.imprimir_baralho();
    std::cout << "\n-----------------------------------\n" << std::endl;
    std::cout << "A carta que comeca o jogo e:" << std::endl;
    monte_principal.imprimir_baralho();
    std::cout << "\n-----------------------------------\n" << std::endl;

    /*
    unsigned int indice_carta;
    cor cor_atual = monte_inicial.get_carta(monte_inicial.get_numero_de_cartas()-1)->get_cor();

    bool curinga;
    if(monte_inicial.get_carta(monte_inicial.get_numero_de_cartas()-1)->get_valor()!=14) {
        curinga = false;
    }
    else {
        curinga = true;
    }
    */
    /*
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

        /*
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
    */

    std::cout << "\n\nPartida finalizada!\n\n";
    std::cout << "Vencedor: Jogador " << c.get_index();
}

void Interface::criaBaralho(){
    /* Implementação do baralho de cartas*/
    monte_compras.criar_interface_monte_comer(visibleSize, origin);
    evento_comprar_carta_interface();
    this->addChild(monte_compras.get_interface_monte_comer());
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchMonteComer,monte_compras.get_interface_monte_comer());
}

void Interface::criaMonte(){
    /* Implementação da última jogada*/
    monte_principal.criar_inteface_monte_jogadas(visibleSize, origin);
    this->addChild(monte_principal.get_inteface_monte_jogadas());
}

void Interface::criaJogador(){
    for(int jogador = 0; jogador < 4; jogador ++){
        for(int posicao_carta = 0; posicao_carta < c.get_jogador_por_indice(jogador)->get_mao()->get_numero_de_cartas(); posicao_carta++){
            adicionarCarta(posicao_carta,jogador);
        }
    }
}

void Interface::adicionarCarta(int posicao_carta, int jogador){
    int rotacao;
    double posicao_x,  posicao_y;
    bool variacao_x, bot;
    cocos2d::Size tamanho;
    switch(jogador){
        case 0:
            tamanho = cocos2d::Size(visibleSize.height/11, visibleSize.height/8);
            posicao_x = origin.x + (visibleSize.width/8) + ((visibleSize.width - (c.get_jogador_por_indice(jogador)->get_mao()->get_numero_de_cartas() * tamanho.width) - (visibleSize.width/4) )/2);
            posicao_y = origin.y + (visibleSize.height/25) ;
            variacao_x = true;
            rotacao = 0;
            bot = false;
            break;
        case 1:
            tamanho = cocos2d::Size(visibleSize.height/11, visibleSize.height/8);
            posicao_x = origin.x + visibleSize.width - tamanho.width - (visibleSize.height/20);
            posicao_y = origin.y + (visibleSize.height/8) + ((visibleSize.height - (7 * visibleSize.height/11) - (visibleSize.height/4) )/2) ;
            variacao_x = false;
            rotacao = 270;
            //Provisorio
            bot = false;
            break;
        case 2:
            tamanho = cocos2d::Size(visibleSize.height/11, visibleSize.height/8);
            posicao_x = origin.x + (visibleSize.width/8) + ((visibleSize.width - (7 * visibleSize.height/11) - (visibleSize.width/4) )/2);
            posicao_y = origin.y + visibleSize.height - tamanho.height - (visibleSize.height/25);
            variacao_x = true;
            rotacao = 0;
            //Provisorio
            bot = false;
            break;
        case 3:
            tamanho = cocos2d::Size(visibleSize.height/11, visibleSize.height/8);
            posicao_x = origin.x + tamanho.width + (visibleSize.height/20);
            posicao_y = origin.y + (visibleSize.height/60) + (visibleSize.height/5) + ((visibleSize.height - (7 * visibleSize.height/11) - (visibleSize.height/4) )/2) ;
            variacao_x = false;
            rotacao = 90;
            //Provisorio
            bot = false;
            break;
    }

    c.get_jogador_por_indice(jogador)->criar_interface_mao(posicao_carta,posicao_x, posicao_y, variacao_x, rotacao, tamanho, bot);
    this->addChild(c.get_jogador_por_indice(jogador)->get_sprite_mao(posicao_carta));

    if(!bot){
        criar_jogar_carta_interface(posicao_carta,jogador);
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchCartas.at(posicao_carta + c.get_jogador_por_indice(jogador)->get_mao()->get_numero_de_cartas()*jogador),c.get_jogador_por_indice(jogador)->get_sprite_mao(posicao_carta));
    }
}

void Interface::evento_comprar_carta_interface(){
    touchMonteComer = cocos2d::EventListenerTouchOneByOne::create();
    touchMonteComer->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        cocos2d::Rect bounds = event->getCurrentTarget()->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())){
            MaoJogador *_mao = c.get_jogador_atual()->get_mao();
            std::vector<Carta*> vetor_temporario = _mao->get_cartas();
            vetor_temporario.push_back(monte_compras.comer_carta());
            _mao->alterar_cartas(vetor_temporario);
            adicionarCarta((_mao->get_numero_de_cartas() - 1),0);
            organizarMaoJogador();
        }
        return true;
    };
}

void Interface::criar_jogar_carta_interface(int posicao_carta, int jogador){
    Carta *carta = c.get_jogador_por_indice(jogador)->get_mao()->get_carta(posicao_carta);
    cocos2d::EventListenerTouchOneByOne* touchCarta = cocos2d::EventListenerTouchOneByOne::create();
    touchCarta->onTouchBegan = [&, carta,jogador](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        cocos2d::Rect bounds = event->getCurrentTarget()->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())){
            if(c.get_index() == jogador)jogarCarta(carta,jogador);
        }
        return true;
    };
    touchCarta->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        organizarMaoJogador();
        return true;
    };
    touchCartas.push_back(touchCarta);
}

void Interface::jogarCarta(Carta *carta_clicada, int jogador){
    int posicao_carta_mao = 0;
    MaoJogador *_mao = c.get_jogador_por_indice(jogador)->get_mao();
    while((carta_clicada->get_valor() != _mao->get_carta(posicao_carta_mao)->get_valor()) || \
    (carta_clicada->get_cor() != _mao->get_carta(posicao_carta_mao)->get_cor())){
        posicao_carta_mao++;
    }
    if(c.get_jogador_por_indice(jogador)->verifica_carta_jogada(posicao_carta_mao, monte_principal.mostrar_topo())){
        _mao->get_interface_carta_mao(posicao_carta_mao)->runAction(cocos2d::MoveTo::create(0.1, cocos2d::Vec2(origin.x + (visibleSize.width/2) - (monte_principal.get_inteface_monte_jogadas()->getContentSize().width/2) , origin.y + (visibleSize.height/2) - (monte_principal.get_inteface_monte_jogadas()->getContentSize().height/2))));
        monte_principal.get_inteface_monte_jogadas()->runAction(cocos2d::RemoveSelf::create(false));
        monte_principal.set_inteface_monte_jogadas( _mao->get_interface_carta_mao(posicao_carta_mao));

        cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(touchCartas.at(posicao_carta_mao));

        monte_principal.adicionar_carta_topo(c.get_jogador_por_indice(jogador)->jogar_carta(posicao_carta_mao, monte_principal.mostrar_topo()));
        _mao->remove_interface_carta_mao(posicao_carta_mao);

        int posicao_carta = posicao_carta_mao;
        for(int i = 0; i < jogador;i++){ //Improviso jogares bot
            posicao_carta += c.get_jogador_por_indice(i)->get_mao()->get_numero_de_cartas();
        }
        touchCartas.erase (touchCartas.begin() + (posicao_carta));
        c.proximo_jogador();
   }

}

void Interface::organizarMaoJogador(){
    for(int jogador = 0; jogador < 4; jogador++){
        for(int posicao_carta = 0; posicao_carta < c.get_jogador_por_indice(jogador)->get_mao()->get_numero_de_cartas(); posicao_carta++){
            double posicao_x;
            double posicao_y;
            bool variando_x;
            switch(jogador){
            case 0:
                posicao_x = origin.x + (visibleSize.width/8) + ((visibleSize.width - (c.get_jogador_por_indice(jogador)->get_mao()->get_numero_de_cartas() * cocos2d::Size(visibleSize.height/11, visibleSize.height/8).width) - (visibleSize.width/4) )/2);
                posicao_y = origin.y + (visibleSize.height/25) ;
                variando_x = true;
                break;
            case 1:
                posicao_x = origin.x + visibleSize.width - cocos2d::Size(visibleSize.height/11, visibleSize.height/8).width - (visibleSize.height/20);
                posicao_y = origin.y + (visibleSize.height/8) + ((visibleSize.height - (c.get_jogador_por_indice(jogador)->get_mao()->get_numero_de_cartas() * visibleSize.height/11) - (visibleSize.height/4) )/2) ;
                variando_x = false;
                break;
            case 2:
                posicao_x = origin.x + (visibleSize.width/8) + ((visibleSize.width - (c.get_jogador_por_indice(jogador)->get_mao()->get_numero_de_cartas() * visibleSize.height/11) - (visibleSize.width/4) )/2);
                posicao_y = origin.y + visibleSize.height - cocos2d::Size(visibleSize.height/11, visibleSize.height/8).height - (visibleSize.height/25);
                variando_x = true;
                break;
            case 3:
                posicao_x = origin.x + cocos2d::Size(visibleSize.height/11, visibleSize.height/8).width + (visibleSize.height/20);
                posicao_y = origin.y + (visibleSize.height/60) + (visibleSize.height/5) + ((visibleSize.height - (c.get_jogador_por_indice(jogador)->get_mao()->get_numero_de_cartas() * visibleSize.height/11) - (visibleSize.height/4) )/2) ;
                variando_x = false;
                break;
            }
            if(variando_x)c.get_jogador_por_indice(jogador)->get_mao()->get_interface_carta_mao(posicao_carta)->setPosition(posicao_x + posicao_carta * c.get_jogador_por_indice(jogador)->get_mao()->get_interface_carta_mao(posicao_carta)->getContentSize().width, posicao_y);
            else c.get_jogador_por_indice(jogador)->get_mao()->get_interface_carta_mao(posicao_carta)->setPosition(posicao_x, posicao_y + posicao_carta * c.get_jogador_por_indice(jogador)->get_mao()->get_interface_carta_mao(posicao_carta)->getContentSize().width);
        }   
    }
}
