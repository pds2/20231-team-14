#include "../../include/interface/interface.hpp"

cocos2d::Scene* Interface::createScene(){
    cocos2d::Scene* scene = cocos2d::Scene::create();
    cocos2d::Layer* layer = Interface::create();
    scene->addChild(layer);
    
    return scene;
}

bool Interface::init(){
    if ( !cocos2d::Layer::init() ){
        return false;
    }

    spritescartas = cocos2d::SpriteFrameCache::getInstance();
    spritescartas->addSpriteFramesWithFile("cartasUno.plist");
    escolhendo_cor = false;
    sistema = new Sistema(4,7);

    cria_baralho();
    cria_monte();
    eventos.cria_eventos_jogar_carta(sistema->get_quantidade_jogadores());
    sprites.inicializa_posicao_cartas(sistema->get_quantidade_jogadores());
    for(int jogador = 0; jogador < sistema->get_quantidade_jogadores(); jogador++){
        cria_jogador(jogador);
    }

    return true;
}

void Interface::cria_baralho(){
    sprites.criar_interface_monte_comer();
    comprar_carta_clique();
    this->addChild(sprites.get_interface_monte_comer());
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventos.get_evento_comprar_carta(),sprites.get_interface_monte_comer());
}

void Interface::cria_monte(){
    sprites.criar_inteface_monte_jogadas(sistema->get_monte_jogadas()->mostrar_topo());
    this->addChild(sprites.get_inteface_monte_jogadas());
}

void Interface::cria_jogador(int jogador){
    for(int posicao_carta = 0; posicao_carta < sistema->get_ciclo()->get_jogador_por_indice(jogador)->get_mao()->get_numero_de_cartas(); posicao_carta++){
        adicionar_carta(posicao_carta,sistema->get_ciclo()->get_jogador_por_indice(jogador));
    }
}

void Interface::adicionar_carta(int posicao_carta, Jogador* jogador){
    sprites.criar_interface_carta_mao(posicao_carta, jogador->get_id(), jogador->get_mao()->get_carta(posicao_carta), jogador->get_mao()->get_numero_de_cartas());
    this->addChild(sprites.get_interface_carta_mao(posicao_carta, jogador->get_id()));
    jogar_carta_clique(posicao_carta,jogador);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(\
    eventos.get_evento_jogar_carta(posicao_carta, jogador->get_id()),sprites.get_interface_carta_mao(posicao_carta, jogador->get_id()));
}

void  Interface::comprar_carta_clique(){
    eventos.adicionar_evento_comprar_carta(cocos2d::EventListenerTouchOneByOne::create());
    //Evento que captura o clique do baralho para comprar uma carta
    eventos.get_evento_comprar_carta()->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        cocos2d::Rect bounds = event->getCurrentTarget()->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())){
            sistema->comprar_carta();
            adicionar_carta((sistema->get_ciclo()->get_jogador_atual()->get_mao()->get_numero_de_cartas() - 1),sistema->get_ciclo()->get_jogador_atual());
            sprites.organizar_mao_jogador(sistema->get_ciclo()->get_jogador_atual()->get_id(),sistema->get_ciclo()->get_jogador_atual()->get_mao()->get_numero_de_cartas());
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
            sprites.organizar_mao_jogador(sistema->get_ciclo()->get_jogador_por_indice(i)->get_id(),sistema->get_ciclo()->get_jogador_por_indice(i)->get_mao()->get_numero_de_cartas());
        }
        return true;
    };
    eventos.adicionar_evento_jogar_carta(touchCarta,jogadorID);
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
    sprites.mover_carta_centro(posicao_carta_mao, sistema->get_ciclo()->get_jogador_atual()->get_id());
    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(eventos.get_evento_jogar_carta(posicao_carta_mao,sistema->get_ciclo()->get_jogador_atual()->get_id()));
    eventos.remover_evento_jogar_carta(posicao_carta_mao,sistema->get_ciclo()->get_jogador_atual()->get_id());
}

void Interface::criar_interface_cor(){
    std::vector<std::string> cores = {"Vermelho.png","Verde.png","Azul.png","Amarelo.png"};

    for(int quadrados = 0; quadrados < 4; quadrados++){
        sprites.cria_interface_escolha_cor(cores.at(quadrados), quadrados);
        //Evento que captura o clique em uma das cores da mudança de cor
        cocos2d::EventListenerTouchOneByOne* touchCor = cocos2d::EventListenerTouchOneByOne::create();
            touchCor->onTouchBegan = [&,quadrados](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
                cocos2d::Rect bounds = event->getCurrentTarget()->getBoundingBox();
                if (bounds.containsPoint(touch->getLocation())){
                    escolhendo_cor = false;
                    sistema->set_cor_atual(cor(quadrados));
                    for(int i = 0; i < 4; i++){
                        cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(eventos.get_evento_escolha_cor(i));
                        sprites.get_interface_escolha_cor(i)->runAction(cocos2d::RemoveSelf::create(false));
                    }
                    sprites.clear_interface_escolha_cor();
                    eventos.clear_evento_escolha_cor();
                }
                return true;
            };
        this->addChild(sprites.get_interface_escolha_cor(quadrados));
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchCor,sprites.get_interface_escolha_cor(quadrados));
        eventos.adicionar_evento_escolha_cor(touchCor);
    }
}   

Interface::~Interface(){
    delete sistema;
}

