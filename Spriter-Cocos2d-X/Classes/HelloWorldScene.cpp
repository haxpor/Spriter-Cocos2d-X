#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // create a label to tell who see the demo
    CCLabelTTF* label = CCLabelTTF::create("Flip X every 2 seconds.\nLeft monster should have bigger head.", "Thonburi", 30);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    label->setPosition( ccp(size.width / 2, size.height - 40) );
    this->addChild(label, 1);

    n1 = SpriterNode::create( "Example.SCML" );
    n1->setPosition( ccp(200, 100) );
    n1->runAnimation( "Idle" );
    
    this->addChild( n1 );
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( "monster.plist" );
    n2 = SpriterNode::create( "Example.SCML", "monster.png" );
    
    n2->setPosition( ccp(600, 100) );
    n2->runAnimation( "Posture" );
    
    this->addChild( n2 );
    this->schedule(schedule_selector(HelloWorld::_flipSpriteX), 2);
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::_flipSpriteX(float df)
{
    // switch back and forth for flipping
    if(n1->getIsFlipX() && n2->getIsFlipX())
    {
        n1->setIsFlipX(false);
        n2->setIsFlipX(false);
    }
    else if(!n1->getIsFlipX() && !n1->getIsFlipX())
    {
        n1->setIsFlipX(true);
        n2->setIsFlipX(true);
    }
    
    CCLog("Called _flipSprite()");
}