#include "../../include/interface/spritesCartas.hpp"
#include <iostream>

USING_NS_CC;

Scene* SpritesCartas::createScene()
{
    auto scene = Scene::create();
    auto layer = SpritesCartas::create();
    scene->addChild(layer);
    
    return scene;
}

bool SpritesCartas::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // load the Sprite Sheet
    auto spritecartas = SpriteFrameCache::getInstance();

    // the .plist file can be generated with any of the tools mentioned below
    spritecartas->addSpriteFramesWithFile("cartasUno.plist");

    /*
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
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,sprite);
    this->addChild(sprite, 0);
    */

    return true;
}


