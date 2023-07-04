#include "../../include/jogador/bot.hpp"

Bot::Bot(int botID){
    this->botID = botID;
}

Bot::Bot(){
    this->botID =0;
}

void Bot::criaBot(cocos2d::Size visibleSize, cocos2d::Vec2 origin){
        /* Implementação bots */
    double posicao_bot_x;
    double posicao_bot_y;
    bool variacao_x;
    int rotacao;
    switch(botID){
        case 0:
            posicao_bot_x = origin.x + (visibleSize.width/8) + ((visibleSize.width - (7 * visibleSize.height/11) - (visibleSize.width/4) )/2);
            posicao_bot_y = origin.y + visibleSize.height - cocos2d::Size(visibleSize.height/11, visibleSize.height/8).height - (visibleSize.height/25);
            variacao_x = true;
            rotacao = 0;
            adicionarBotTela(posicao_bot_x, posicao_bot_y, variacao_x,7,rotacao,botID,visibleSize,origin);
            break;
        case 1:
            posicao_bot_x = origin.x + cocos2d::Size(visibleSize.height/11, visibleSize.height/11).width + (visibleSize.height/20);
            posicao_bot_y = origin.y + (visibleSize.height/60) + (visibleSize.height/5) + ((visibleSize.height - (7 * visibleSize.height/11) - (visibleSize.height/4) )/2) ;
            variacao_x = false;
            rotacao = 90;
            adicionarBotTela(posicao_bot_x, posicao_bot_y, variacao_x,7,rotacao,botID,visibleSize,origin);
            break;
        case 2:
            posicao_bot_x = origin.x + visibleSize.width - cocos2d::Size(visibleSize.height/11, visibleSize.height/11).width - (visibleSize.height/20);
            posicao_bot_y = origin.y + (visibleSize.height/8) + ((visibleSize.height - (7 * visibleSize.height/11) - (visibleSize.height/4) )/2) ;
            variacao_x = false;
            rotacao = 270;
            adicionarBotTela(posicao_bot_x, posicao_bot_y, variacao_x,7,rotacao,botID,visibleSize,origin);
            break;
    }
}

void Bot::adicionarBotTela(double posicao_bot_x, double posicao_bot_y, bool variando_x, int quantidade_cartas, int rotacao,int botID,cocos2d::Size visibleSize, cocos2d::Vec2 origin){
    for(int i=0; i < quantidade_cartas;i++){
        cocos2d::Sprite* carta_bot = cocos2d::Sprite::createWithSpriteFrameName("card_back.png");
        carta_bot->setAnchorPoint(cocos2d::Vec2(0, 0));
        carta_bot->setContentSize(cocos2d::Size(visibleSize.height/11, visibleSize.height/8));
        if(variando_x){
            carta_bot->setPosition(posicao_bot_x + i * carta_bot->getContentSize().width, posicao_bot_y);
        }else{
            carta_bot->setPosition(posicao_bot_x, posicao_bot_y + i * carta_bot->getContentSize().width);
        }
        carta_bot->runAction(cocos2d::RotateTo::create(0,rotacao));
        
        cartas_bot.push_back(carta_bot);
    }
}

cocos2d::Sprite* Bot::get_interface_carta_bot(int indice){
    return cartas_bot.at(indice);
}

void Bot::jogarCartaInterface(){
    /*
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
         */
}