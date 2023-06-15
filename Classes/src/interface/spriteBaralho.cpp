#include "../../include/interface/spriteBaralho.hpp"
#include <iostream>

USING_NS_CC;

Scene* SpriteBaralho::createScene()
{
    auto scene = Scene::create();
    auto layer = SpriteBaralho::create();
    scene->addChild(layer);
    
    return scene;
}

bool SpriteBaralho::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("BaralhoUno.png");
    sprite->setContentSize(Size(80, 80));
    sprite->setAnchorPoint(Vec2(0, 0));
    float x = origin.x;
    float y = origin.y + visibleSize.height - sprite->getContentSize().height;
    sprite->setPosition(x, y);

    auto touchListener = EventListenerTouchOneByOne::create();
     touchListener->onTouchBegan = [](Touch* touch, Event* event) -> bool {
        auto bounds = event->getCurrentTarget()->getBoundingBox();
        if (bounds.containsPoint(touch->getLocation())){
            std::cout << "Compra uma carta" << std::endl;
        }
        return true;
    };

    auto spritecartas = SpriteFrameCache::getInstance();

    spritecartas->addSpriteFramesWithFile("cartasUno.plist");

    auto azul_0 = Sprite::createWithSpriteFrameName("blue_0.png");

    azul_0->setAnchorPoint(Vec2(0, 0));
    azul_0->setPosition(origin.x, origin.y);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,sprite);
    this->addChild(sprite, 0);
    this->addChild(azul_0, 0);

    return true;
}


