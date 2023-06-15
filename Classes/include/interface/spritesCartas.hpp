#ifndef SPRITES_CARTAS_HPP
#define SPRITES_CARTAS_HPP

#include "cocos2d.h"

class SpritesCartas : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(SpritesCartas);
};

#endif