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

void Interface::criaPartida(){
    escolhendo_cor = false;
    qntd_jogadores = 4;
    c = Ciclo();

    MonteCartasIniciais monte_inicial = MonteCartasIniciais();
    monte_inicial.embaralhar_cartas();

    int numero_cartas_iniciais = 7;
    // Cria os jogadores e suas cartas
    for(int i = 1; i <= qntd_jogadores ; i++){
        std::vector<Carta*> mao_atual = monte_inicial.distribuir_mao_inicial(numero_cartas_iniciais);
        c.adicionar_jogadores(new Jogador(i));
        c.get_jogador(i)->receber_cartas(new MaoJogador(numero_cartas_iniciais, mao_atual));
        inicializa_posicao_jogador(i);
    }

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
    curinga = false;
}

void Interface::inicializa_posicao_jogador(int index){
    int rotacao;
    double posicao_x,  posicao_y;
    bool variacao_x, bot;
    cocos2d::Size tamanho;
    switch(index-1){
        case 0:
            tamanho = cocos2d::Size(visibleSize.height/11, visibleSize.height/8);
            posicao_x = origin.x + (visibleSize.width/8) + ((visibleSize.width - (visibleSize.width/3) )/2) + (visibleSize.height/50) ;
            posicao_y = origin.y + (visibleSize.height/25) ;
            variacao_x = true;
            rotacao = 0;
            bot = false;
            break;
        case 1:
            tamanho = cocos2d::Size(visibleSize.height/11, visibleSize.height/8);
            posicao_x = origin.x + visibleSize.width - tamanho.width - (visibleSize.height/20);
            posicao_y = origin.y + (visibleSize.height/8) + ((visibleSize.height - (visibleSize.height/3) )/2) + (visibleSize.height/50)  ;
            variacao_x = false;
            rotacao = 270;
            //Provisorio
            bot = false;
            break;
        case 2:
            tamanho = cocos2d::Size(visibleSize.height/11, visibleSize.height/8);
            posicao_x = origin.x + (visibleSize.width/8) + ((visibleSize.width  - (visibleSize.width/3) )/2) + (visibleSize.height/50) ;
            posicao_y = origin.y + visibleSize.height - tamanho.height - (visibleSize.height/25);
            variacao_x = true;
            rotacao = 0;
            //Provisorio
            bot = false;
            break;
        case 3:
            tamanho = cocos2d::Size(visibleSize.height/11, visibleSize.height/8);
            posicao_x = origin.x + tamanho.width + (visibleSize.height/20);
            posicao_y = origin.y + (visibleSize.height/60) + (visibleSize.height/5) + ((visibleSize.height  - (visibleSize.height/3) )/2) + (visibleSize.height/50)  ;
            variacao_x = false;
            rotacao = 90;
            //Provisorio
            bot = false;
            break;
    }

    c.get_jogador(index)->inicializa_posicao_cartas(posicao_x, posicao_y, variacao_x, rotacao, tamanho, bot);
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
    for(int jogador = 0; jogador < qntd_jogadores; jogador ++){
        for(int posicao_carta = 0; posicao_carta < c.get_jogador_por_indice(jogador)->get_mao()->get_numero_de_cartas(); posicao_carta++){
            adicionarCarta(posicao_carta,c.get_jogador_atual());
        }
        c.proximo_jogador();
    }
}

void Interface::adicionarCarta(int posicao_carta, Jogador* jogador){
    jogador->criar_interface_mao(posicao_carta);
    this->addChild(jogador->get_sprite_mao(posicao_carta));
    criar_jogar_carta_interface(posicao_carta,jogador);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority((jogador->get_evento(posicao_carta)),jogador->get_sprite_mao(posicao_carta));
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
            adicionarCarta((_mao->get_numero_de_cartas() - 1),c.get_jogador_atual());
            c.get_jogador_atual()->organizar_mao_jogador();
        }
        return true;
    };
}

void Interface::criar_jogar_carta_interface(int posicao_carta, Jogador* jogador){
    Carta *carta = jogador->get_mao()->get_carta(posicao_carta);
    cocos2d::EventListenerTouchOneByOne* touchCarta = cocos2d::EventListenerTouchOneByOne::create();
    int jogadorID = jogador->get_id();
    touchCarta->onTouchBegan = [&, carta,jogadorID](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        cocos2d::Rect bounds = event->getCurrentTarget()->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())){
            if(!escolhendo_cor && (c.get_jogador_atual()->get_id() == jogadorID)) jogarCarta(carta); 
        }
        return true;
    };
    touchCarta->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        for(int i = 0; i < qntd_jogadores; i++){
            c.get_jogador_por_indice(i)->organizar_mao_jogador();
        }
        return true;
    };
    jogador->adicionar_evento(touchCarta);
}

void Interface::jogarCarta(Carta *carta_clicada){
    int posicao_carta_mao = 0;
    MaoJogador *_mao = c.get_jogador_atual()->get_mao();
    while((carta_clicada->get_valor() != _mao->get_carta(posicao_carta_mao)->get_valor()) || \
    (carta_clicada->get_cor() != _mao->get_carta(posicao_carta_mao)->get_cor())){
        posicao_carta_mao++;
    }

    if(curinga==false) {
        if(c.get_jogador_atual()->verifica_carta_jogada(posicao_carta_mao, monte_principal.mostrar_topo())){
            monte_principal.adicionar_carta_topo(c.get_jogador_atual()->jogar_carta(posicao_carta_mao, monte_principal.mostrar_topo()));
            modifica_carta(posicao_carta_mao,_mao);
        }
    }else{
        if(c.get_jogador_atual()->verifica_cor_jogada(posicao_carta_mao, cor_atual)){
            monte_principal.adicionar_carta_topo(c.get_jogador_atual()->jogar_carta_apenas_pela_cor(posicao_carta_mao, cor_atual));
            modifica_carta(posicao_carta_mao,_mao);
        }
    }
}

void Interface::modifica_carta(int posicao_carta_mao, MaoJogador *_mao){
    _mao->get_interface_carta_mao(posicao_carta_mao)->runAction(cocos2d::MoveTo::create(0.1, cocos2d::Vec2(origin.x + (visibleSize.width/2) - (monte_principal.get_inteface_monte_jogadas()->getContentSize().width/2) , origin.y + (visibleSize.height/2) - (monte_principal.get_inteface_monte_jogadas()->getContentSize().height/2))));
    monte_principal.get_inteface_monte_jogadas()->runAction(cocos2d::RemoveSelf::create(false));
    monte_principal.set_inteface_monte_jogadas( _mao->get_interface_carta_mao(posicao_carta_mao));
    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(c.get_jogador_atual()->get_evento(posicao_carta_mao));
    _mao->remove_interface_carta_mao(posicao_carta_mao);
    c.get_jogador_atual()->remover_evento(posicao_carta_mao);
    aplicaCartaEspecial();
    c.proximo_jogador();   
}

void Interface::aplicaCartaEspecial(){    
    bool pular_vez = false;
    valor checar_especial = monte_principal.mostrar_topo()->get_valor();
    switch(checar_especial) {
        case valor(10):
            c.inverter();
            break;
        case valor(11):
            c.proximo_jogador();
            break;
        case valor(12):
            for(int i=0; i<2; i++) {
                if(c.get_index() == qntd_jogadores-1) {
                    c.get_jogador_por_indice(0)->get_mao()->comprar_carta(monte_compras.comer_carta());
                    adicionarCarta((c.get_jogador_por_indice(0)->get_mao()->get_numero_de_cartas() - 1),c.get_jogador_por_indice(0));
                }
                else {
                    c.get_proximo_jogador()->get_mao()->comprar_carta(monte_compras.comer_carta());
                    adicionarCarta((c.get_proximo_jogador()->get_mao()->get_numero_de_cartas() - 1),c.get_proximo_jogador());
                }
            }
            break;
        case valor(13): 
            for(int i=0; i<4; i++) {
                if(c.get_index() == qntd_jogadores-1) {
                    c.get_jogador_por_indice(0)->get_mao()->comprar_carta(monte_compras.comer_carta());
                    adicionarCarta((c.get_jogador_por_indice(0)->get_mao()->get_numero_de_cartas() - 1),c.get_jogador_por_indice(0));
                }
                else {
                    c.get_proximo_jogador()->get_mao()->comprar_carta(monte_compras.comer_carta());
                    adicionarCarta((c.get_proximo_jogador()->get_mao()->get_numero_de_cartas() - 1),c.get_proximo_jogador());
                }
            }
            break;
    }
    cor checar_mudanca_de_cor = monte_principal.mostrar_topo()->get_cor();
    if(checar_mudanca_de_cor == cor(4)) {
        curinga = true;
        escolhendo_cor = true;
        criar_interface_cor();

    }else{
        curinga = false;
    }

}

void Interface::criar_interface_cor(){
    std::vector<std::string> cores = {"Vermelho.png","Verde.png","Azul.png","Amarelo.png"};


    for(int quadrados = 0; quadrados < 4; quadrados++){
        cocos2d::Sprite* quadrado_cor = cocos2d::Sprite::create(cores.at(quadrados));
        quadrado_cor->setContentSize(cocos2d::Size(visibleSize.height/10, visibleSize.width/15));
        quadrado_cor->setAnchorPoint(cocos2d::Vec2(0, 0));
        float x;
        float y;
        if(quadrados < 2){
            x = origin.x + visibleSize.height/2 + visibleSize.height/10  + quadrado_cor->getContentSize().height*quadrados;
            y = origin.y + visibleSize.width/3;
        }else{
            x = origin.x + visibleSize.height/2 + visibleSize.height/10  + quadrado_cor->getContentSize().height*(quadrados-2);
            y = origin.y + visibleSize.width/3 - quadrado_cor->getContentSize().width;
        }
        quadrado_cor->setPosition(x, y);

        cocos2d::EventListenerTouchOneByOne* touchCor = cocos2d::EventListenerTouchOneByOne::create();
            touchCor->onTouchBegan = [&,quadrados](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
                cocos2d::Rect bounds = event->getCurrentTarget()->getBoundingBox();
                if (bounds.containsPoint(touch->getLocation())){
                    escolhendo_cor = false;
                    cor_atual = cor(quadrados);

                    for(int i = 0; i < 4; i++){
                        cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(touchCores.at(i));
                        quadrados_cor.at(i)->runAction(cocos2d::RemoveSelf::create(false));
                    }
                    quadrados_cor.clear();
                    touchCores.clear();

                }
                return true;
            };
        this->addChild(quadrado_cor);
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchCor,quadrado_cor);
        quadrados_cor.push_back(quadrado_cor);
        touchCores.push_back(touchCor);
        
    }
}   

