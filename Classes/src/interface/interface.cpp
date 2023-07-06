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
    cria_partida();

    return true;
}

void Interface::setar_curinga() {
    if(monte_principal->get_carta(monte_principal->get_numero_de_cartas()-1)->get_valor()!=14)
        curinga = false;
    else 
        curinga = true;
}

MonteCartasIniciais* Interface::preparar_monte_inicial() {
    MonteCartasIniciais* monte_inicial = new MonteCartasIniciais();
    monte_inicial->embaralhar_cartas();
    return monte_inicial;
}

void Interface::preparar_monte_cartas_jogadas(MonteCartasIniciais* monte_inicial) {
    std::vector<Carta*> inicio;
    inicio.push_back(monte_inicial->selecionar_carta_inicial());
    monte_principal = new MonteCartasJogadas(inicio);
    cria_monte();
}

void Interface::preparar_monte_cartas_para_compra(MonteCartasIniciais* monte_inicial) {
    monte_compras = new MonteCartasComer(qntd_cartas_iniciais, qntd_jogadores, monte_inicial->get_cartas());
    monte_inicial->limpar_cartas();
    cria_baralho();
}

void Interface::preparar_jogadores(MonteCartasIniciais* monte_inicial) {
    for(int i = 0; i < qntd_jogadores; i++){
        std::vector<Carta*> mao_atual = monte_inicial->distribuir_mao_inicial(qntd_cartas_iniciais);
        Jogador *jogador = new Jogador(i);
        c->adicionar_jogadores(jogador);
        c->get_jogador(i)->receber_cartas(new MaoJogador(qntd_cartas_iniciais, mao_atual));
        inicializa_posicao_jogador(i);
        cria_jogador(i);
    }
}

void Interface::cria_partida(){
    escolhendo_cor = false;
    qntd_jogadores = 4;
    qntd_cartas_iniciais = 7;

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
}

void Interface::inicializa_posicao_jogador(int index){
    int rotacao;
    double posicao_x,  posicao_y;
    bool variacao_x, bot;
    cocos2d::Size tamanho;
    switch(index){
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

    c->get_jogador(index)->inicializa_posicao_cartas(posicao_x, posicao_y, variacao_x, rotacao, tamanho, bot);
}

void Interface::cria_baralho(){
    monte_compras->criar_interface_monte_comer(visibleSize, origin);
    comprar_carta();
    this->addChild(monte_compras->get_interface_monte_comer());
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchMonteComer,monte_compras->get_interface_monte_comer());
}

void Interface::cria_monte(){
    monte_principal->criar_inteface_monte_jogadas(visibleSize, origin);
    this->addChild(monte_principal->get_inteface_monte_jogadas());
}

void Interface::cria_jogador(int jogador){
    for(int posicao_carta = 0; posicao_carta < c->get_jogador_por_indice(jogador)->get_mao()->get_numero_de_cartas(); posicao_carta++){
        adicionar_carta(posicao_carta,c->get_jogador_por_indice(jogador));
    }
}

void Interface::adicionar_carta(int posicao_carta, Jogador* jogador){
    jogador->criar_interface_mao(posicao_carta);
    this->addChild(jogador->get_sprite_mao(posicao_carta));
    jogar_carta_clique(posicao_carta,jogador);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority((jogador->get_evento(posicao_carta)),jogador->get_sprite_mao(posicao_carta));
}

void Interface::comprar_carta(){
    touchMonteComer = cocos2d::EventListenerTouchOneByOne::create();

    //Evento que captura o clique do baralho para comprar uma carta
    touchMonteComer->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        cocos2d::Rect bounds = event->getCurrentTarget()->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())){
            checar_reinicio_monte_compras();
            c->get_jogador_atual()->get_mao()->comprar_carta(monte_compras->comer_carta()); //Mudei coisa aqui
            adicionar_carta((c->get_jogador_atual()->get_mao()->get_numero_de_cartas() - 1),c->get_jogador_atual());
            c->get_jogador_atual()->organizar_mao_jogador();
        }
        return true;
    };
}

void Interface::checar_reinicio_monte_compras(){
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

void Interface::jogar_carta_clique(int posicao_carta, Jogador* jogador){
    Carta *carta = jogador->get_mao()->get_carta(posicao_carta);
    cocos2d::EventListenerTouchOneByOne* touchCarta = cocos2d::EventListenerTouchOneByOne::create();
    int jogadorID = jogador->get_id();

    //Evento que captura o clique em uma das cartas da mão do jogador
    touchCarta->onTouchBegan = [&, carta,jogadorID](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        cocos2d::Rect bounds = event->getCurrentTarget()->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())){
            if(!escolhendo_cor && (c->get_jogador_atual()->get_id() == jogadorID)) jogar_carta(carta); 
        }
        return true;
    };
    touchCarta->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        for(int i = 0; i < qntd_jogadores; i++){
            c->get_jogador_por_indice(i)->organizar_mao_jogador();
        }
        return true;
    };
    jogador->adicionar_evento(touchCarta);
}

void Interface::jogar_carta(Carta *carta_clicada){
    int posicao_carta_mao = 0;
    MaoJogador *_mao = c->get_jogador_atual()->get_mao();
    while((carta_clicada->get_valor() != _mao->get_carta(posicao_carta_mao)->get_valor()) || \
    (carta_clicada->get_cor() != _mao->get_carta(posicao_carta_mao)->get_cor())){
        posicao_carta_mao++;
    }
    fazer_jogada(posicao_carta_mao,_mao);
}

void Interface::fazer_jogada(int indice_carta,MaoJogador *_mao){
    if(curinga==false) {
        if(c->get_jogador_atual()->verifica_carta_jogada(indice_carta, monte_principal->mostrar_topo())){
            monte_principal->adicionar_carta_topo(c->get_jogador_atual()->jogar_carta(indice_carta, monte_principal->mostrar_topo()));
            mandar_carta(indice_carta,_mao);
        }
    }else{
        if(c->get_jogador_atual()->verifica_cor_jogada(indice_carta, cor_atual)){
            monte_principal->adicionar_carta_topo(c->get_jogador_atual()->jogar_carta_apenas_pela_cor(indice_carta, cor_atual));
            mandar_carta(indice_carta,_mao);
        }
    }    
}

void Interface::mandar_carta(int posicao_carta_mao, MaoJogador *_mao){
    _mao->get_interface_carta_mao(posicao_carta_mao)->runAction(cocos2d::MoveTo::create(0.1, cocos2d::Vec2(\
    origin.x + (visibleSize.width/2) - (monte_principal->get_inteface_monte_jogadas()->getContentSize().width/2) ,\
    origin.y + (visibleSize.height/2) - (monte_principal->get_inteface_monte_jogadas()->getContentSize().height/2))));
    monte_principal->get_inteface_monte_jogadas()->runAction(cocos2d::RemoveSelf::create(false));
    monte_principal->set_inteface_monte_jogadas( _mao->get_interface_carta_mao(posicao_carta_mao));
    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(c->get_jogador_atual()->get_evento(posicao_carta_mao));
    _mao->remove_interface_carta_mao(posicao_carta_mao);
    c->get_jogador_atual()->remover_evento(posicao_carta_mao);

    if (c->get_jogador_atual()->verificar_vitoria()){
        _partida_finalizada = true;
        std::cout << "Partida finalizada" << std::endl;
        std::cout << "Vencedor jogador " << c->get_jogador_atual()->get_id() << std::endl;
        //Chamar funções de vencer jogo 
        cocos2d::Director::getInstance()->end();
    } 

    aplicar_efeito_especial();
    c->proximo_jogador();   
}

void Interface::aplicar_efeito_especial(){    
    bool pular_vez = false;
    valor checar_especial = monte_principal->mostrar_topo()->get_valor();
    switch(checar_especial) {
        case valor(10):
            c->inverter();
            break;
        case valor(11):
            c->proximo_jogador();
            break;
        case valor(12):
            for(int i=0; i<2; i++) {
                aplicar_compra_proximo_jogador();
            }
            break;
        case valor(13): 
            for(int i=0; i<4; i++) {
                aplicar_compra_proximo_jogador();
            }
            break;
    }
    aplicar_mudanca_cor();
}

void Interface::aplicar_compra_proximo_jogador(){
    checar_reinicio_monte_compras();
    if(c->get_index() == qntd_jogadores-1) {
        c->get_jogador_por_indice(0)->get_mao()->comprar_carta(monte_compras->comer_carta());
        adicionar_carta((c->get_jogador_por_indice(0)->get_mao()->get_numero_de_cartas() - 1),c->get_jogador_por_indice(0));
    }else {
        c->get_proximo_jogador()->get_mao()->comprar_carta(monte_compras->comer_carta());
        adicionar_carta((c->get_proximo_jogador()->get_mao()->get_numero_de_cartas() - 1),c->get_proximo_jogador());
    }    
}

void Interface::aplicar_mudanca_cor(){
    cor checar_mudanca_de_cor = monte_principal->mostrar_topo()->get_cor();
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
        float x = origin.x + visibleSize.height/2 + visibleSize.height/10  + quadrado_cor->getContentSize().height*(quadrados-2);
        float y = origin.y + visibleSize.width/3 - quadrado_cor->getContentSize().width;
        if(quadrados < 2){
            x = origin.x + visibleSize.height/2 + visibleSize.height/10  + quadrado_cor->getContentSize().height*quadrados;
            y = origin.y + visibleSize.width/3;
        }
        quadrado_cor->setPosition(x, y);
        
        //Evento que captura o clique em uma das cores da mudança de cor
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

