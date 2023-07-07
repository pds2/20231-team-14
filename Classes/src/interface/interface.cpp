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
    escolhendo_cor = false;
    sistema = new Sistema(4,7);

    cria_baralho();
    cria_monte();
    for(int jogador = 0; jogador < sistema->get_quantidade_jogadores(); jogador++){
        inicializa_posicao_jogador(jogador);
        cria_jogador(jogador);
    }

    return true;
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

    sistema->get_ciclo()->get_jogador(index)->inicializa_posicao_cartas(posicao_x, posicao_y, variacao_x, rotacao, tamanho, bot);
}

void Interface::cria_baralho(){
    sistema->get_monte_compras()->criar_interface_monte_comer(visibleSize, origin);
    comprar_carta_clique();
    this->addChild(sistema->get_monte_compras()->get_interface_monte_comer());
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchMonteComer,sistema->get_monte_compras()->get_interface_monte_comer());
}

void Interface::cria_monte(){
    sistema->get_monte_jogadas()->criar_inteface_monte_jogadas(visibleSize, origin);
    this->addChild(sistema->get_monte_jogadas()->get_inteface_monte_jogadas());
}

void Interface::cria_jogador(int jogador){
    for(int posicao_carta = 0; posicao_carta < sistema->get_ciclo()->get_jogador_por_indice(jogador)->get_mao()->get_numero_de_cartas(); posicao_carta++){
        adicionar_carta(posicao_carta,sistema->get_ciclo()->get_jogador_por_indice(jogador));
    }
}

void Interface::adicionar_carta(int posicao_carta, Jogador* jogador){
    jogador->criar_interface_mao(posicao_carta);
    this->addChild(jogador->get_sprite_mao(posicao_carta));
    jogar_carta_clique(posicao_carta,jogador);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority((jogador->get_evento(posicao_carta)),jogador->get_sprite_mao(posicao_carta));
}

void  Interface::comprar_carta_clique(){
    touchMonteComer = cocos2d::EventListenerTouchOneByOne::create();
    //Evento que captura o clique do baralho para comprar uma carta
    touchMonteComer->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        cocos2d::Rect bounds = event->getCurrentTarget()->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())){
            sistema->comprar_carta();
            adicionar_carta((sistema->get_ciclo()->get_jogador_atual()->get_mao()->get_numero_de_cartas() - 1),sistema->get_ciclo()->get_jogador_atual());
            sistema->get_ciclo()->get_jogador_atual()->organizar_mao_jogador();
        }
        return true;
    };
}

void Interface::jogar_carta_clique(int posicao_carta, Jogador* jogador){
    Carta *carta = jogador->get_mao()->get_carta(posicao_carta);
    cocos2d::EventListenerTouchOneByOne* touchCarta = cocos2d::EventListenerTouchOneByOne::create();
    int jogadorID = jogador->get_id();

    //Evento que captura o clique em uma das cartas da mão do jogador
    touchCarta->onTouchBegan = [&, carta,jogadorID](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        cocos2d::Rect bounds = event->getCurrentTarget()->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())){
            organizar_jogada(carta,jogadorID);
        }
        return true;
    };
    touchCarta->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        for(int i = 0; i < sistema->get_quantidade_jogadores(); i++){
            sistema->get_ciclo()->get_jogador_por_indice(i)->organizar_mao_jogador();
        }
        return true;
    };
    jogador->adicionar_evento(touchCarta);
}

void Interface::organizar_jogada(Carta* carta, int jogadorID){
    if(!escolhendo_cor && (sistema->get_ciclo()->get_jogador_atual()->get_id() == jogadorID)){
        int indice = sistema->definir_indice_carta_jogada(carta);
        bool jogada_possivel = sistema->jogar_carta(indice);
        if(jogada_possivel){
            jogar_sprite_carta(indice);

            if (sistema->get_ciclo()->get_jogador_atual()->verificar_vitoria()){
                std::cout << "Partida finalizada" << std::endl;
                std::cout << "Vencedor jogador " << sistema->get_ciclo()->get_jogador_atual()->get_id() << std::endl;
                //Chamar funções de vencer jogo 
                cocos2d::Director::getInstance()->end();
            } 

            int quantidade_cartas_comprar = sistema->aplicar_efeito_especial();
            for(int quantidade = 0; quantidade < quantidade_cartas_comprar; quantidade++){
                if(sistema->get_ciclo()->get_index() == sistema->get_quantidade_jogadores()-1) {
                    adicionar_carta((sistema->get_ciclo()->get_jogador_por_indice(0)->get_mao()->get_numero_de_cartas() - quantidade_cartas_comprar + quantidade),sistema->get_ciclo()->get_jogador_por_indice(0));
                }else{
                    adicionar_carta((sistema->get_ciclo()->get_proximo_jogador()->get_mao()->get_numero_de_cartas() - quantidade_cartas_comprar + quantidade),sistema->get_ciclo()->get_proximo_jogador());
                }
            } 

            escolhendo_cor = sistema->checa_mudanca_cor();
            if(escolhendo_cor)criar_interface_cor();
            sistema->get_ciclo()->proximo_jogador();
        }
    }
}

void Interface::jogar_sprite_carta(int posicao_carta_mao){
    sistema->get_ciclo()->get_jogador_atual()->get_mao()->get_interface_carta_mao(posicao_carta_mao)->runAction(cocos2d::MoveTo::create(0.1, cocos2d::Vec2(\
    origin.x + (visibleSize.width/2) - (sistema->get_monte_jogadas()->get_inteface_monte_jogadas()->getContentSize().width/2) ,\
    origin.y + (visibleSize.height/2) - (sistema->get_monte_jogadas()->get_inteface_monte_jogadas()->getContentSize().height/2))));
    sistema->get_monte_jogadas()->get_inteface_monte_jogadas()->runAction(cocos2d::RemoveSelf::create(false));
    sistema->get_monte_jogadas()->set_inteface_monte_jogadas(sistema->get_ciclo()->get_jogador_atual()->get_mao()->get_interface_carta_mao(posicao_carta_mao));
    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(sistema->get_ciclo()->get_jogador_atual()->get_evento(posicao_carta_mao));
    sistema->get_ciclo()->get_jogador_atual()->get_mao()->remove_interface_carta_mao(posicao_carta_mao);
    sistema->get_ciclo()->get_jogador_atual()->remover_evento(posicao_carta_mao);
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
                    sistema->set_cor_atual(cor(quadrados));

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

Interface::~Interface(){
    delete sistema;
}

