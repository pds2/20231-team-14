#include "../../include/interface/spriteBaralho.hpp"

cocos2d::Scene* SpriteBaralho::createScene(){
    cocos2d::Scene* scene = cocos2d::Scene::create();
    cocos2d::Layer* layer = SpriteBaralho::create();
    scene->addChild(layer);
    
    return scene;
}

bool SpriteBaralho::init(){
    if ( !cocos2d::Layer::init() )
    {
        return false;
    }
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    spritescartas = cocos2d::SpriteFrameCache::getInstance();
    spritescartas->addSpriteFramesWithFile("cartasUno.plist");

    tamanhoCarta = visibleSize.height/11;
    larguraCarta = visibleSize.width/11;

    criaBaralho();
    criaMonte();
    criaJogador();
    criaBot(0);
    criaBot(1);
    criaBot(2);

    return true;
}

void SpriteBaralho::criaBaralho(){
    /* Implementação do baralho de cartas*/
    baralho = cocos2d::Sprite::create("BaralhoUno.png");
    baralho->setContentSize(cocos2d::Size(visibleSize.height/7, visibleSize.width/7));
    baralho->setAnchorPoint(cocos2d::Vec2(0, 0));
    float x = origin.x;
    float y = origin.y + visibleSize.height - baralho->getContentSize().height;
    baralho->setPosition(x, y);
    touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        cocos2d::Rect bounds = event->getCurrentTarget()->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())){
            maoJogador.push_back(Carta(MAIS_DOIS, AZUL)); //Receber a carta para comprar
            adicionarCarta(Carta(MAIS_DOIS, AZUL),maoJogador.size() - 1);

            /* Teste mão bots
            double posicao_bot_x;
            double posicao_bot_y;
            bool variacao_x;
            posicao_bot_x = origin.x + (visibleSize.width/8) + ((visibleSize.width - (quantidade_cartas.at(0) * tamanhoCarta) - (visibleSize.width/4) )/2);
            posicao_bot_y = origin.y + visibleSize.height - cocos2d::Size(tamanhoCarta, larguraCarta).height - (visibleSize.height/25);
            variacao_x = true;
            jogarCartaBot(0, Carta(N7, AMARELO),posicao_bot_x, posicao_bot_y,variacao_x);
            */


            std::cout << "Compra uma carta" << std::endl; //Chamar a função que compra uma carta
        }
        return true;
    };
    this->addChild(baralho);

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,baralho);
}

void SpriteBaralho::criaBot(int botID){
    /* Implementação bots */
    double posicao_bot_x;
    double posicao_bot_y;
    bool variacao_x;
    int rotacao;
    quantidade_cartas.push_back(7); //Receber a quantidade de cartas que cada bot possui
    switch(botID){
        case 0:
            posicao_bot_x = origin.x + (visibleSize.width/8) + ((visibleSize.width - (quantidade_cartas.at(botID) * tamanhoCarta) - (visibleSize.width/4) )/2);
            posicao_bot_y = origin.y + visibleSize.height - cocos2d::Size(tamanhoCarta, larguraCarta).height - (visibleSize.height/25);
            variacao_x = true;
            rotacao = 0;
            adicionarBotTela(posicao_bot_x, posicao_bot_y, variacao_x,quantidade_cartas.at(botID),rotacao,botID);
            break;
        case 1:
            posicao_bot_x = origin.x + cocos2d::Size(tamanhoCarta, larguraCarta).width + (visibleSize.height/20);
            posicao_bot_y = origin.y + (visibleSize.height/60) + (visibleSize.height/5) + ((visibleSize.height - (quantidade_cartas.at(botID) * tamanhoCarta) - (visibleSize.height/4) )/2) ;
            variacao_x = false;
            rotacao = 90;
            adicionarBotTela(posicao_bot_x, posicao_bot_y, variacao_x,quantidade_cartas.at(botID),rotacao,botID);
            break;
        case 2:
            posicao_bot_x = origin.x + visibleSize.width - cocos2d::Size(tamanhoCarta, larguraCarta).width - (visibleSize.height/20);
            posicao_bot_y = origin.y + (visibleSize.height/8) + ((visibleSize.height - (quantidade_cartas.at(botID) * tamanhoCarta) - (visibleSize.height/4) )/2) ;
            variacao_x = false;
            rotacao = 270;
            adicionarBotTela(posicao_bot_x, posicao_bot_y, variacao_x,quantidade_cartas.at(botID),rotacao,botID);
            break;
    }
}

void SpriteBaralho::adicionarBotTela(double posicao_bot_x, double posicao_bot_y, bool variando_x, int quantidade_cartas, int rotacao,int botID){
    for(int i=0; i < quantidade_cartas;i++){
        cocos2d::Sprite* carta_bot = cocos2d::Sprite::createWithSpriteFrameName("card_back.png");
        carta_bot->setAnchorPoint(cocos2d::Vec2(0, 0));
        carta_bot->setContentSize(cocos2d::Size(tamanhoCarta, larguraCarta));
        if(variando_x){
            carta_bot->setPosition(posicao_bot_x + i * carta_bot->getContentSize().width, posicao_bot_y);
        }else{
            carta_bot->setPosition(posicao_bot_x, posicao_bot_y + i * carta_bot->getContentSize().width);
        }
        this->addChild(carta_bot);
        carta_bot->runAction(cocos2d::RotateTo::create(0,rotacao));

        //Improviso
        switch(botID){
            case 0:
                cartas_bot0.push_back(carta_bot);
                break;
            case 1:
                cartas_bot1.push_back(carta_bot);
                break;
            case 2:
                cartas_bot2.push_back(carta_bot);
                break;
        }
    }
}

void SpriteBaralho::jogarCartaBot(int botID, Carta carta_jogada,double posicao_bot_x, double posicao_bot_y, bool variando_x){
    quantidade_cartas.at(botID)--;
    int posicao_bot_carta = 0;
    std::list<cocos2d::Sprite*>::iterator iterator_bot;
    switch(botID){
        case 0:
            iterator_bot = cartas_bot0.begin();
            (*iterator_bot)->runAction(cocos2d::RemoveSelf::create(false));
            cartas_bot0.pop_front();
            for(iterator_bot = cartas_bot0.begin(); iterator_bot!= cartas_bot0.end(); iterator_bot++){
                if(variando_x){
                    (*iterator_bot)->setPosition(posicao_bot_x + posicao_bot_carta * (*iterator_bot)->getContentSize().width, posicao_bot_y);
                }else{
                    (*iterator_bot)->setPosition(posicao_bot_x, posicao_bot_y + posicao_bot_carta * (*iterator_bot)->getContentSize().width);
                }
                posicao_bot_carta++;
            }
            break;
        case 1:
            iterator_bot = cartas_bot1.begin();
            (*iterator_bot)->runAction(cocos2d::RemoveSelf::create(false));
            cartas_bot0.pop_front();
            for(iterator_bot = cartas_bot1.begin(); iterator_bot!= cartas_bot1.end(); iterator_bot++){
                if(variando_x){
                    (*iterator_bot)->setPosition(posicao_bot_x + posicao_bot_carta * (*iterator_bot)->getContentSize().width, posicao_bot_y);
                }else{
                    (*iterator_bot)->setPosition(posicao_bot_x, posicao_bot_y + posicao_bot_carta * (*iterator_bot)->getContentSize().width);
                }
                posicao_bot_carta++;
            }
            break;
        case 2:
            iterator_bot = cartas_bot2.begin();
            (*iterator_bot)->runAction(cocos2d::RemoveSelf::create(false));
            cartas_bot0.pop_front();
            for(iterator_bot = cartas_bot2.begin(); iterator_bot!= cartas_bot2.end(); iterator_bot++){
                if(variando_x){
                    (*iterator_bot)->setPosition(posicao_bot_x + posicao_bot_carta * (*iterator_bot)->getContentSize().width, posicao_bot_y);
                }else{
                    (*iterator_bot)->setPosition(posicao_bot_x, posicao_bot_y + posicao_bot_carta * (*iterator_bot)->getContentSize().width);
                }
                posicao_bot_carta++;
            }
            break;
    }




}

void SpriteBaralho::criaJogador(){
    /* Implementação mão do Jogador*/
    maoJogador.push_back(Carta(N7, AMARELO));
    maoJogador.push_back(Carta(PULA_VEZ, VERDE));
    maoJogador.push_back(Carta(N2, AZUL));
    maoJogador.push_back(Carta(N5, VERMELHO));
    maoJogador.push_back(Carta(MAIS_QUATRO, PRETA));
    maoJogador.push_back(Carta(N9, VERDE));
    maoJogador.push_back(Carta(MAIS_DOIS, VERMELHO));
    /* Receber aqui a mão do jogador da classe MaoJogador*/

    int posicao_carta = 0;
    std::list<Carta>::iterator iterator_carta = maoJogador.begin();
    for(iterator_carta = maoJogador.begin(); iterator_carta!= maoJogador.end(); iterator_carta++){
        adicionarCarta(*(iterator_carta),posicao_carta);
        posicao_carta++;
    }

}

void SpriteBaralho::criaMonte(){
    /* Implementação da última jogada*/
    Carta carta = Carta(MAIS_DOIS, AMARELO); //Receber carta jogada por último
    carta_jogada = cocos2d::Sprite::createWithSpriteFrameName(carta.get_sprite());
    carta_jogada->setAnchorPoint(cocos2d::Vec2(0, 0));
    carta_jogada->setContentSize(cocos2d::Size(tamanhoCarta, larguraCarta));
    carta_jogada->setPosition(origin.x + (visibleSize.width/2) - (carta_jogada->getContentSize().width/2) , origin.y + (visibleSize.height/2) - (carta_jogada->getContentSize().height/2));
    this->addChild(carta_jogada);
}

void SpriteBaralho::eventoCliqueCarta(Carta carta_clicada){
    int posicao_carta_mao = 0;
    std::list<Carta>::iterator iterator_carta = maoJogador.begin();
    for(iterator_carta = maoJogador.begin(); iterator_carta!= maoJogador.end(); iterator_carta++){
        if((carta_clicada.get_valor() == iterator_carta->get_valor()) && (carta_clicada.get_cor() == iterator_carta->get_cor())){
            break;
        }
        posicao_carta_mao++;
    }
    Carta carta_selecionada = (*iterator_carta);
    std::cout << "Joga uma carta" << std::endl; //Chamar a função para jogar uma carta
    //A carta jogada foi a "carta_selecionada"


    /*Executar se for possível jogar a carta selecionada*/
    std::list<cocos2d::Sprite*>::iterator iterator_mao = cartas_mao.begin();
    advance(iterator_mao,posicao_carta_mao);
    (*iterator_mao)->runAction(cocos2d::MoveTo::create(0.1, cocos2d::Vec2(origin.x + (visibleSize.width/2) - (carta_jogada->getContentSize().width/2) , origin.y + (visibleSize.height/2) - (carta_jogada->getContentSize().height/2))));
    carta_jogada->runAction(cocos2d::RemoveSelf::create(false));
    carta_jogada = (*iterator_mao);

    std::list<cocos2d::EventListenerTouchOneByOne*>::iterator iterator_eventos = touchCartas.begin();
    advance(iterator_eventos,posicao_carta_mao);

    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener((*iterator_eventos));

    cartas_mao.erase (iterator_mao);
    maoJogador.erase (iterator_carta);
    touchCartas.erase (iterator_eventos);
}

void SpriteBaralho::adicionarCarta(Carta maoCarta, int posicao_carta){
    cocos2d::Sprite* carta_mao = cocos2d::Sprite::createWithSpriteFrameName(maoCarta.get_sprite());
    carta_mao->setAnchorPoint(cocos2d::Vec2(0, 0));
    carta_mao->setContentSize(cocos2d::Size(tamanhoCarta, larguraCarta));
    double posicao_mao = origin.x + (visibleSize.width/8) + ((visibleSize.width - (maoJogador.size() * carta_mao->getContentSize().width) - (visibleSize.width/4) )/2);
    carta_mao->setPosition(posicao_mao + posicao_carta * carta_mao->getContentSize().width, origin.y + (visibleSize.height/25));

    cocos2d::EventListenerTouchOneByOne* touchCarta = cocos2d::EventListenerTouchOneByOne::create();
    touchCarta->onTouchBegan = [&, maoCarta](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        cocos2d::Rect bounds = event->getCurrentTarget()->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())){
            Carta carta_clicada = maoCarta;
            eventoCliqueCarta(carta_clicada);
        }
        return true;
    };

    touchCarta->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
    organizarMaoJogador();
        return true;
    };
    cartas_mao.push_back(carta_mao);
    touchCartas.push_back(touchCarta);
    this->addChild(carta_mao);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchCarta,carta_mao);
}

void SpriteBaralho::organizarMaoJogador(){
    int posicao_carta = 0;
    for(cocos2d::Sprite* carta_mao: cartas_mao){
        double posicao_mao = origin.x + (visibleSize.width/8) + ((visibleSize.width - (maoJogador.size() * carta_mao->getContentSize().width) - (visibleSize.width/4) )/2);
        carta_mao->setPosition(posicao_mao + posicao_carta * carta_mao->getContentSize().width, origin.y + (visibleSize.height/25));
        posicao_carta++;
    }    
}


