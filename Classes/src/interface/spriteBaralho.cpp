#include "../../include/interface/spriteBaralho.hpp"

cocos2d::Scene* SpriteBaralho::createScene()
{
    cocos2d::Scene* scene = cocos2d::Scene::create();
    cocos2d::Layer* layer = SpriteBaralho::create();
    scene->addChild(layer);
    
    return scene;
}

bool SpriteBaralho::init()
{
    if ( !cocos2d::Layer::init() )
    {
        return false;
    }
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    spritescartas = cocos2d::SpriteFrameCache::getInstance();
    spritescartas->addSpriteFramesWithFile("cartasUno.plist");

    criaBaralho();
    criaMonte();
    criaJogador();
    criaBot();

    return true;
}

void SpriteBaralho::criaBaralho(){
    /* Implementação do baralho de cartas*/
    baralho = cocos2d::Sprite::create("BaralhoUno.png");
    baralho->setContentSize(cocos2d::Size(visibleSize.height/5, visibleSize.width/5));
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

            std::cout << "Compra uma carta" << std::endl; //Chamar a função que compra uma carta
        }
        return true;
    };
    this->addChild(baralho);

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,baralho);
}

void SpriteBaralho::criaBot(){
    /* Implementação bots */
    double posicao_bot_acima = 0;
    int quantidade_cartas = 7; //Receber a quantidade de cartas que cada bot possui

    for(int i=0; i < quantidade_cartas;i++){

        cocos2d::Sprite* carta_bot = cocos2d::Sprite::createWithSpriteFrameName("card_back.png");
        carta_bot->setAnchorPoint(cocos2d::Vec2(0, 0));
        carta_bot->setContentSize(cocos2d::Size(visibleSize.height/9, visibleSize.width/9));
        posicao_bot_acima = origin.x + (visibleSize.width/8) + ((visibleSize.width - (quantidade_cartas * carta_bot->getContentSize().width) - (visibleSize.width/4) )/2);
        carta_bot->setPosition(posicao_bot_acima + i * carta_bot->getContentSize().width, origin.y + visibleSize.height - carta_bot->getContentSize().height - (visibleSize.height/20));
        this->addChild(carta_bot);
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
    carta_jogada->setContentSize(cocos2d::Size(visibleSize.height/9, visibleSize.width/9));
    carta_jogada->setPosition(origin.x + (visibleSize.width/2) - (carta_jogada->getContentSize().width/2) , origin.y + (visibleSize.height/2) - (carta_jogada->getContentSize().height/2));
    this->addChild(carta_jogada);
}


void SpriteBaralho::adicionarCarta(Carta maoCarta, int posicao_carta){
    cocos2d::Sprite* carta_mao = cocos2d::Sprite::createWithSpriteFrameName(maoCarta.get_sprite());
    carta_mao->setAnchorPoint(cocos2d::Vec2(0, 0));
    carta_mao->setContentSize(cocos2d::Size(visibleSize.height/9, visibleSize.width/9));
    double posicao_mao = origin.x + (visibleSize.width/8) + ((visibleSize.width - (maoJogador.size() * carta_mao->getContentSize().width) - (visibleSize.width/4) )/2);
    carta_mao->setPosition(posicao_mao + posicao_carta * carta_mao->getContentSize().width, origin.y + (visibleSize.height/20));

    cocos2d::EventListenerTouchOneByOne* touchCarta = cocos2d::EventListenerTouchOneByOne::create();
    touchCarta->onTouchBegan = [&, maoCarta](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        cocos2d::Rect bounds = event->getCurrentTarget()->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())){

            int posicao_carta_mao = 0;
            Carta carta_clicada = maoCarta;
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
        return true;
    };

    touchCarta->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        int posicao_carta = 0;
        for(cocos2d::Sprite* carta_mao: cartas_mao){
            double posicao_mao = origin.x + (visibleSize.width/8) + ((visibleSize.width - (maoJogador.size() * carta_mao->getContentSize().width) - (visibleSize.width/4) )/2);
            carta_mao->setPosition(posicao_mao + posicao_carta * carta_mao->getContentSize().width, origin.y + (visibleSize.height/20));
            posicao_carta++;
        }
        return true;
    };
    cartas_mao.push_back(carta_mao);
    touchCartas.push_back(touchCarta);
    this->addChild(carta_mao);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchCarta,carta_mao);
}


