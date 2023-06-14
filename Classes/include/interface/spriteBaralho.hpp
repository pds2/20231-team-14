#ifndef SPRITE_BARALHO_HPP
#define SPRITE_BARALHO_HPP

#include "cocos2d.h"

class SpriteBaralho : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(SpriteBaralho);
};

#endif