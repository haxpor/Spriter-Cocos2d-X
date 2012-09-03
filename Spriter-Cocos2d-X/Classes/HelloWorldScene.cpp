#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SpriterNode.h"

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

    SpriterNode *n = SpriterNode::create( "Example.SCML" );
    
    n->setPosition( ccp(200, 100) );
    n->runAnimation( "Idle" );
    
    this->addChild( n );
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( "monster.plist" );
    n = SpriterNode::create( "Example.SCML", "monster.png" );
    
    n->setPosition( ccp(600, 100) );
    n->runAnimation( "Posture" );
    
    this->addChild( n );
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
