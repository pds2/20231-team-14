#include "../../include/interface/sprites.hpp"
#include <iostream>

Sprites::Sprites(){
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    spritescartas = cocos2d::SpriteFrameCache::getInstance();
    spritescartas->addSpriteFramesWithFile("cartasUno.plist");
    spritescartaspretas= cocos2d::SpriteFrameCache::getInstance();
    spritescartaspretas->addSpriteFramesWithFile("cartas_especias_coloridas.plist");
}

std::string Sprites::get_sprite(Carta* carta){
    return (std::to_string(carta->get_valor()) + "_" + std::to_string(carta->get_cor()) + ".png");
}

void Sprites::inicializa_posicao_cartas(int qntd_jogadores){
    tamanho = cocos2d::Size(visibleSize.height/11, visibleSize.height/8);

    for(int i = 0; i < qntd_jogadores;i++){
        rotacao.push_back(360 - (i * 90));
        bot.push_back(true); 

        if((i%2) != 0){
            variacao_x.push_back(false);
            posicao_y.push_back(origin.y + (visibleSize.height/8) + ((visibleSize.height - (visibleSize.height/3) )/2) + (visibleSize.height/40) + ((i - 1) * tamanho.width - tamanho.height/6)/2);
            if(i == 1)posicao_x.push_back(origin.x + visibleSize.width - tamanho.width - (visibleSize.height/10));
            else posicao_x.push_back(origin.x + tamanho.width + (visibleSize.height/10));

        }else{
            variacao_x.push_back(true);
            posicao_x.push_back(origin.x + (visibleSize.width/8) + ((visibleSize.width - (visibleSize.width/3) )/2) + (visibleSize.height/50) + (i * (tamanho.width + tamanho.height/10))/2 );
            posicao_y.push_back(origin.y + (visibleSize.height/25) + ((i * visibleSize.height)/2) - ((visibleSize.height/25) * i));
        }

        if(i == 0) bot.at(i) = false;

        std::vector<cocos2d::Sprite*> cartas_jogador;
        cartas_mao.push_back(cartas_jogador);
    }
}

bool Sprites::is_bot(int jogador){
    return bot.at(jogador);
}

// carta -> get_carta da carta mao do jogador
void Sprites::criar_interface_carta_mao(int posicao_carta, int jogador, Carta* carta, int numero_cartas){
    cocos2d::Sprite* carta_mao;
    if(bot.at(jogador)) carta_mao = cocos2d::Sprite::createWithSpriteFrameName("card_back.png");
    else carta_mao = cocos2d::Sprite::createWithSpriteFrameName(get_sprite(carta));
    carta_mao->setAnchorPoint(cocos2d::Vec2(0, 0));
    carta_mao->setContentSize(tamanho);
    if(variacao_x.at(jogador)){
        double posicao_x_temporaria = posicao_x.at(jogador) - (numero_cartas * tamanho.height)/3;
        carta_mao->setPosition(posicao_x_temporaria + posicao_carta * carta_mao->getContentSize().width, posicao_y.at(jogador));
    } else{
        double posicao_y_temporaria = posicao_y.at(jogador) - (numero_cartas * tamanho.height)/3;
        carta_mao->setPosition(posicao_x.at(jogador), posicao_y_temporaria + posicao_carta * carta_mao->getContentSize().width);
    }
    carta_mao->runAction(cocos2d::RotateTo::create(0,rotacao.at(jogador)));
    cartas_mao.at(jogador).push_back(carta_mao);
}

void Sprites::mostra_carta_bot(int posicao_carta, int jogador, Carta* carta){
    cartas_mao.at(jogador).at(posicao_carta)->setSpriteFrame(get_sprite(carta));
    cartas_mao.at(jogador).at(posicao_carta)->setContentSize(tamanho);
}

cocos2d::Sprite* Sprites::get_interface_carta_mao(int indice, int jogador){
    return cartas_mao.at(jogador).at(indice);
}   

void Sprites::mover_carta_centro(int posicao_carta_mao, int jogador){
    cartas_mao.at(jogador).at(posicao_carta_mao)->runAction(cocos2d::MoveTo::create(0.1, cocos2d::Vec2(origin.x + (visibleSize.width/2) - (tamanho.width/2) ,origin.y + (visibleSize.height/2) - (tamanho.height/2))));
    carta_jogada->runAction(cocos2d::RemoveSelf::create(false));
    carta_jogada = cartas_mao.at(jogador).at(posicao_carta_mao);
    cartas_mao.at(jogador).erase(cartas_mao.at(jogador).begin() + posicao_carta_mao);
}

cocos2d::Sprite* Sprites::get_interface_monte_comer(){
    return cartasComerSprite;
}   

void Sprites::criar_interface_monte_comer(){
    cartasComerSprite = cocos2d::Sprite::create("BaralhoUno.png");
    cartasComerSprite->setContentSize(cocos2d::Size(visibleSize.height/7, visibleSize.width/7));
    cartasComerSprite->setAnchorPoint(cocos2d::Vec2(0, 0));
    float x = origin.x;
    float y = origin.y + visibleSize.height - cartasComerSprite->getContentSize().height;
    cartasComerSprite->setPosition(x, y);
}

void Sprites::criar_inteface_monte_jogadas(Carta* carta_inicio){
    carta_jogada = cocos2d::Sprite::createWithSpriteFrameName(get_sprite(carta_inicio));
    carta_jogada->setAnchorPoint(cocos2d::Vec2(0, 0));
    carta_jogada->setContentSize(cocos2d::Size(visibleSize.height/11, visibleSize.width/11));
    carta_jogada->setPosition(origin.x + (visibleSize.width/2) - (carta_jogada->getContentSize().width/2) , origin.y + (visibleSize.height/2) - (carta_jogada->getContentSize().height/2));
}

cocos2d::Sprite* Sprites::get_inteface_monte_jogadas(){
    return carta_jogada;
}

void Sprites::organizar_mao_jogador(int jogador, int numero_de_cartas){
    double posicao_x_temporaria = posicao_x.at(jogador);
    double posicao_y_temporaria = posicao_y.at(jogador);
    if(variacao_x.at(jogador)) posicao_x_temporaria -= (numero_de_cartas * tamanho.height)/3;
    else posicao_y_temporaria -=(numero_de_cartas * tamanho.height)/3;

    for(int posicao_carta = 0; posicao_carta < numero_de_cartas; posicao_carta++){
        if(variacao_x.at(jogador)){
            cartas_mao.at(jogador).at(posicao_carta)->setPosition(posicao_x_temporaria + posicao_carta * cartas_mao.at(jogador).at(posicao_carta)->getContentSize().width, posicao_y_temporaria);
        }else {
            cartas_mao.at(jogador).at(posicao_carta)->setPosition(posicao_x_temporaria, posicao_y_temporaria + posicao_carta * cartas_mao.at(jogador).at(posicao_carta)->getContentSize().width);
        }
    }  
}

void Sprites::cria_interface_escolha_cor(std::string cor, int quadrados){
    cocos2d::Sprite* quadrado_cor = cocos2d::Sprite::create(cor);
    quadrado_cor->setContentSize(cocos2d::Size(visibleSize.height/10, visibleSize.width/15));
    quadrado_cor->setAnchorPoint(cocos2d::Vec2(0, 0));
    float x = origin.x + visibleSize.height/2 + visibleSize.height/10  + quadrado_cor->getContentSize().height*(quadrados-2);
    float y = origin.y + visibleSize.width/3 - quadrado_cor->getContentSize().width;
    if(quadrados < 2){
        x = origin.x + visibleSize.height/2 + visibleSize.height/10  + quadrado_cor->getContentSize().height*quadrados;
        y = origin.y + visibleSize.width/3;
    }
    quadrado_cor->setPosition(x, y);   
    escolha_cores.push_back(quadrado_cor);
}

void Sprites::muda_cor_curinga(Carta* carta, cor cor_escolihida){
    std::string carta_sprite = (std::to_string(carta->get_valor()) + "_" + std::to_string(carta->get_cor()) + "_" + std::to_string(cor_escolihida) + ".png");
    carta_jogada->setSpriteFrame(carta_sprite);
    carta_jogada->setContentSize(tamanho);
}

cocos2d::Sprite* Sprites::get_interface_escolha_cor(int indice){
    return escolha_cores.at(indice);
}


void Sprites::clear_interface_escolha_cor(){
    escolha_cores.clear();
}