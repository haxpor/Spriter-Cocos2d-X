//
//  SpriterNode.cpp
//  Tank
//
//  Created by Young Peter on 9/1/12.
//  http://weibo.com/young40
//
//

#include "SpriterNode.h"

USING_NS_CC;

#pragma mark SpriterConfigNode
SpriterConfigNode::SpriterConfigNode()
{
    this->_children = new CCArray();
    this->_properties = new CCDictionary();
    this->_parent = NULL;
}

SpriterConfigNode::~SpriterConfigNode()
{
    if (this->_children) {
        this->_children->autorelease();
    }
    if (this->_properties) {
        this->_properties->autorelease();
    }
}

SpriterConfigNode* SpriterConfigNode::create(const char *name)
{
    SpriterConfigNode *node = new SpriterConfigNode();
    
    node->_name = name;
    
    return node;
}

SpriterConfigNode* SpriterConfigNode::getParent()
{
    return this->_parent;
}

void SpriterConfigNode::setParent(SpriterConfigNode *parent)
{
    this->_parent = parent;
}

const char* SpriterConfigNode::getName()
{
    return this->_name;
}

CCArray* SpriterConfigNode::getChildren()
{
    return this->_children;
}

SpriterConfigNode* SpriterConfigNode::getChildrenAt(int index)
{
    if (index<_children->count())
    {
        return (SpriterConfigNode*)_children->objectAtIndex(index);
    }
    
    return NULL;
}

int SpriterConfigNode::getChildrenCount()
{
    return _children->count();
}

CCDictionary* SpriterConfigNode::getProperties()
{
    return this->_properties;
}

CCString* SpriterConfigNode::getPropertyCCString(const char *key)
{
    CCObject *obj = _properties->objectForKey(key);
    
    if (obj)
    {
        return (CCString*)obj;
    }
    
    return CCString::create("");
}

#pragma mark SpriterObjectRef
SpriterObjectRef* SpriterObjectRef::create()
{
    return new SpriterObjectRef();
}

int SpriterObjectRef::getTimelineId()
{
    return _timelineId;
}

void SpriterObjectRef::setTimelineId(int timelineId)
{
    _timelineId = timelineId;
}

int SpriterObjectRef::getTimelineKey()
{
    return _timelineKey;
}

void SpriterObjectRef::setTimelineKey(int timelineKey)
{
    _timelineKey = timelineKey;
}
#pragma mark TGSpriterMainlineKey

SpriterMainlineKey* SpriterMainlineKey::create()
{
    SpriterMainlineKey *key = new SpriterMainlineKey();
    
    key->_objectRefs = new CCArray();
    
    return key;
}

void SpriterMainlineKey::addObjectRef(SpriterObjectRef *objectRef)
{
    _objectRefs->addObject(objectRef);
}

CCArray* SpriterMainlineKey::getObjectRefs()
{
    return _objectRefs;
}

SpriterTimeline* SpriterTimeline::create()
{
    SpriterTimeline *line = new SpriterTimeline();
    line->_keys = new CCArray();
    return line;
}

void SpriterTimeline::addKeyFrame(SpriterTimelineKey *frame)
{
    _keys->addObject(frame);
}

CCArray* SpriterTimeline::getKeys()
{
    return _keys;
}

SpriterTimelineKey* SpriterTimelineKey::create()
{
    SpriterTimelineKey *key = new SpriterTimelineKey();
    
    return key;
}

int SpriterTimelineKey::getFileId()
{
    return _file;
}

void SpriterTimelineKey::setFileId(int id)
{
    _file = id;
}

int SpriterTimelineKey::getFolderId()
{
    return _folder;
}

void SpriterTimelineKey::setFolderId(int id)
{
    _folder = id;
}

double SpriterTimelineKey::getStartsAt()
{
    return _startsAt;
}

void SpriterTimelineKey::setStartsAt(double index)
{
    _startsAt = index;
}

CCPoint SpriterTimelineKey::getPostion()
{
    return _position;
}

void SpriterTimelineKey::setPostion(cocos2d::CCPoint postion)
{
    _position = postion;
}

CCPoint SpriterTimelineKey::getAnchorPoint()
{
    return _anchorPoint;
}

void SpriterTimelineKey::setAnchorPoint(cocos2d::CCPoint anchorPoint)
{
    _anchorPoint = anchorPoint;
}

double SpriterTimelineKey::getRotation()
{
    return _rotation;
}

void SpriterTimelineKey::setRotation(double rotation)
{
    _rotation = rotation;
}

int SpriterTimelineKey::getSpin()
{
    return _spin;
}

void SpriterTimelineKey::setSpin(int spin)
{
    _spin = spin;
}

double SpriterTimelineKey::getScaleX()
{
    return _scaleX;
}

void SpriterTimelineKey::setScaleX(double scaleX)
{
    _scaleX = scaleX;
}

double SpriterTimelineKey::getScaleY()
{
    return _scaleY;
}

void SpriterTimelineKey::setScaleY(double scaleY)
{
    _scaleY = scaleY;
}

SpriterAnimation::SpriterAnimation()
{
    _mainline = new CCArray();
    _timelines = new CCArray();
}

SpriterAnimation::~SpriterAnimation()
{
    if (_mainline)
    {
        _mainline->removeAllObjects();
        _mainline->release();
        _mainline = NULL;
    }
    if (_timelines)
    {
        _timelines->removeAllObjects();
        _timelines->release();
        _timelines = NULL;
    }
}

SpriterAnimation* SpriterAnimation::create()
{
    return new SpriterAnimation();
}

const char* SpriterAnimation::getName()
{
    return this->_name;
}

void SpriterAnimation::addKeyFrame(SpriterMainlineKey *frame)
{
    _mainline->addObject(frame);
}

void SpriterAnimation::setName(const char *name)
{
    this->_name = name;
}

double SpriterAnimation::getDuration()
{
    return this->_duration;
}

void SpriterAnimation::setDuration(double duration)
{
    this->_duration = duration;
}

void SpriterAnimation::addTimeline(SpriterTimeline *timeline)
{
    _timelines->addObject(timeline);
}

CCArray* SpriterAnimation::getMainline()
{
    return _mainline;
}

CCArray* SpriterAnimation::getTimelines()
{
    return _timelines;
}

SpriterNode::SpriterNode()
{
    _playbackSpeed = 1.0;
    
    _configRoot = NULL;
    _curConfigNode = NULL;
    
    _files = new CCDictionary();
    
    _animations = new CCDictionary();
    _frames = new CCDictionary();
    
    _spriteNodes = new CCArray();
}

SpriterNode::~SpriterNode()
{
    if (_files)
    {
        _files->release();
        _files = NULL;
    }
    
    if (_animations)
    {
        _animations->release();
        _animations = NULL;
    }
    if (_frames)
    {
        _frames->release();
        _frames = NULL;
    }
    if (_spriteNodes)
    {
        _spriteNodes->removeAllObjects();
        _spriteNodes->release();
        _spriteNodes = NULL;
    }
}

SpriterNode * SpriterNode::create(const char *scmlFile)
{
    SpriterNode * pNode = new SpriterNode();
    
    if (pNode->initNodeWithFile(scmlFile))
    {
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_DELETE(pNode);
    return NULL;
}

SpriterNode* SpriterNode::create(const char *scmlFile, const char *imageFile)
{
    SpriterNode * pNode = new SpriterNode();
    
    pNode->_useBatchNode = true;
    pNode->_batchNode = CCSpriteBatchNode::create(imageFile);
    pNode->addChild(pNode->_batchNode);
    
    if (pNode->initNodeWithFile(scmlFile))
    {
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_DELETE(pNode);
    return NULL;
}


bool SpriterNode::initNodeWithFile(const char *scmlFile)
{
    CCAssert(scmlFile != NULL && strlen(scmlFile)>0, "SpriterNode: SCML file should not be NULL");
    
    this->setContentSize(CCSizeZero);
    
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(scmlFile);
    
    CCSAXParser parser;
    
    if (false == parser.init("UTF-8") )
    {
        return false;
    }
    
    parser.setDelegator(this);
    
    bool rs = parser.parse(path);
    
    initObjects();
    
    return rs;
}

void SpriterNode::initObjects()
{
    for (int i=0; i<_configRoot->getChildrenCount(); i++)
    {
        SpriterConfigNode *c = _configRoot->getChildrenAt(i);
        //CCLog("%s", c->getName());
        
        if (!strncmp(c->getName(), "folder", strlen(c->getName())))
        {
            for (int j=0; j<c->getChildrenCount(); j++)
            {
                SpriterConfigNode *file = c->getChildrenAt(j);
                
                CCString *fileKey =
                    CCString::createWithFormat(
                                               "%d-%d",
                                                c->getPropertyCCString("id")->intValue(),
                                                file->getPropertyCCString("id")->intValue());
                
                std::string strFile = (char*)file->getPropertyCCString("name")->getCString();
                std::string pattern = "/";
                
                std::string::size_type pos;
                std::vector<std::string> result;
                
                strFile += pattern;
                
                int size = strFile.size();
                
                for (int i=0; i<size; i++)
                {
                    pos = strFile.find(pattern, i);
                    
                    if(pos<size)
                    {
                        std::string s = strFile.substr(i, pos-i);
                        result.push_back(s);
                        i=pos+pattern.size()-1;
                    }
                }
                
                std::string _file = result[result.size()-1];
                
                //CCLog("%s", CCString::create(_file)->getCString());
                
                _files->setObject(CCString::create(_file), fileKey->getCString());
            }
        }
        else if(!strncmp(c->getName(), "entity", strlen(c->getName())))
        {
            for (int k=0; k<c->getChildrenCount(); k++)
            {
                SpriterConfigNode *animation = c->getChildrenAt(k);
                
                SpriterAnimation *spriterAnimation = SpriterAnimation::create();
                spriterAnimation->setName(animation->getPropertyCCString("name")->getCString());
                spriterAnimation->setDuration(animation->getPropertyCCString("length")->doubleValue());
                
                //CCLog("Parsing Animation: %s %f", spriterAnimation->getName(), spriterAnimation->getDuration());
                
                for (int l=0; l<animation->getChildrenCount(); l++)
                {
                    SpriterConfigNode *animConfig = animation->getChildrenAt(l);
                    
                    if (!strncmp(animConfig->getName(), "mainline", strlen(animConfig->getName())))
                    {
                        for (int m=0; m<animConfig->getChildrenCount(); m++)
                        {
                            SpriterConfigNode *key = animConfig->getChildrenAt(m);
                            SpriterMainlineKey *mainlineKey = SpriterMainlineKey::create();
                            
                            for (int n=0; n<key->getChildrenCount(); n++)
                            {
                                SpriterConfigNode *object_ref = key->getChildrenAt(n);
                                
                                SpriterObjectRef *objectRef = SpriterObjectRef::create();
                                
                                objectRef->setTimelineId(object_ref->getPropertyCCString("timeline")->intValue());
                                objectRef->setTimelineKey(object_ref->getPropertyCCString("key")->intValue());
                                
                                mainlineKey->addObjectRef(objectRef);                                
                            }
                            spriterAnimation->addKeyFrame(mainlineKey);
                        }
                    }
                    else if(!strncmp(animConfig->getName(), "timeline", strlen(animConfig->getName())))
                    {
                        SpriterTimeline *timeline = SpriterTimeline::create();
                        
                        for (int p=0; p<animConfig->getChildrenCount(); p++)
                        {
                            SpriterConfigNode *key = animConfig->getChildrenAt(p);
                            
                            for (int q=0; q<key->getChildrenCount(); q++)
                            {
                                SpriterConfigNode *object = key->getChildrenAt(q);
                                
                                SpriterTimelineKey *timelineKey = SpriterTimelineKey::create();
                                
                                timelineKey->setFolderId(object->getPropertyCCString("folder")->intValue());
                                timelineKey->setFileId(object->getPropertyCCString("file")->intValue());
                                timelineKey->setPostion(
                                                        ccp(object->getPropertyCCString("x")->doubleValue(),
                                                            object->getPropertyCCString("y")->doubleValue()) );
                                timelineKey->setAnchorPoint(
                                    ccp(object->getPropertyCCString("pivot_x")->doubleValue(),
                                        object->getPropertyCCString("pivot_y")->doubleValue()));
                                timelineKey->setStartsAt(key->getPropertyCCString("time")->doubleValue());
                                timelineKey->setRotation(object->getPropertyCCString("angle")->doubleValue());
                                
                                if(object->getPropertyCCString("scale_x")->doubleValue())
                                {
                                    timelineKey->setScaleX(object->getPropertyCCString("scale_x")->doubleValue());
                                }
                                else
                                {
                                    timelineKey->setScaleX(1.0);
                                }
                                
                                if(object->getPropertyCCString("scale_y")->doubleValue())
                                {
                                    timelineKey->setScaleY(object->getPropertyCCString("scale_y")->doubleValue());
                                }
                                else
                                {
                                    timelineKey->setScaleY(1.0);
                                }
                                    
                                
                                if (key->getPropertyCCString("spin")->intValue())
                                {
                                    timelineKey->setSpin(key->getPropertyCCString("spin")->intValue());
                                }
                                else
                                {
                                    timelineKey->setSpin(1);
                                }
                                
                                timeline->addKeyFrame(timelineKey);
                            }
                        }
                        
                        spriterAnimation->addTimeline(timeline);
                    }
                }
                
                _animations->setObject(spriterAnimation, spriterAnimation->getName());
            }
        }
    }
    
    if ( _configRoot )
    {
        _configRoot->release();
        _configRoot = NULL;
    }
}    

void SpriterNode::startElement(void *ctx, const char *name, const char **atts)
{
    CC_UNUSED_PARAM(ctx);
    
    if ( _configRoot == NULL)
    {
        _configRoot = SpriterConfigNode::create( name );
        _curConfigNode = _configRoot;
        return;
    }
    
    SpriterConfigNode *newNode = SpriterConfigNode::create( name );
    
    newNode->setParent( _curConfigNode );

    if (atts && atts[0]) {
        for (int i=0; atts[i]; i+=2)
        {
            std::string key = (char*)atts[i];
            std::string value = (char*)atts[i+1];
            
            newNode->getProperties()->setObject( CCString::create( value ), key );
        }
    }
    
    _curConfigNode->getChildren()->addObject( newNode );
    _curConfigNode = newNode;
}

void SpriterNode::endElement(void *ctx, const char *name)
{
    _curConfigNode = _curConfigNode->getParent();
}

void SpriterNode::textHandler(void *ctx, const char *ch, int len)
{
}

void SpriterNode::runAnimation(const char *animation)
{
    unschedule(schedule_selector(SpriterNode::update));
    
    _duration = 0;
    _frameIndex = 0;
    
    _curAnimation = (SpriterAnimation*)_animations->objectForKey(animation);
    _curKeyFrame = (SpriterMainlineKey*)_curAnimation->getMainline()->objectAtIndex(0);
    _nextKeyFrame = (SpriterMainlineKey*)_curAnimation->getMainline()->objectAtIndex((_frameIndex+1)%_curAnimation->getMainline()->count());
    
    
    schedule(schedule_selector(SpriterNode::update));
}

void SpriterNode::update(float dt)
{
    CCLog("%f", dt);//Cocos2d: 0.016306
    
    _duration += dt;
    
    int milliseconds = _duration * 10000 * _playbackSpeed;
    int startTime = _curKeyFrame->getStartsAt();
    int endTime = _nextKeyFrame->getStartsAt();
    
    if (endTime == 0.0f)
    {
        endTime = _curAnimation->getDuration();
    }
    
    if (milliseconds > endTime)
    {
        _curKeyFrame = _nextKeyFrame;
        _frameIndex = (_frameIndex+1)%_curAnimation->getMainline()->count();
        _nextKeyFrame = (SpriterMainlineKey*)_curAnimation->getMainline()->objectAtIndex((_frameIndex+1)%_curAnimation->getMainline()->count());
        startTime = _curKeyFrame->getStartsAt();
        endTime = _nextKeyFrame->getStartsAt();
    }
    if (milliseconds > _curAnimation->getDuration())
    {
        _duration -= milliseconds * 0.0001/_playbackSpeed;
        milliseconds -= 10000 * _playbackSpeed;
    }
    
    for (int i=0; i<_spriteNodes->count(); i++)
    {
        ((CCSprite*)_spriteNodes->objectAtIndex(i))->setVisible(false);
    }
    
    // interpolation
    double interpolationFactor = ((milliseconds - startTime)/(1.0*(endTime-startTime)));
    
    for (int i=0; i<_curKeyFrame->getObjectRefs()->count(); i++)
    {
        SpriterObjectRef *curObjectRef = (SpriterObjectRef*)_curKeyFrame->getObjectRefs()->objectAtIndex(i);
        SpriterObjectRef *nextObjectRef = (SpriterObjectRef*)_nextKeyFrame->getObjectRefs()->objectAtIndex(i);
        
        SpriterTimeline *objectTimeline = (SpriterTimeline*)_curAnimation->getTimelines()->objectAtIndex(curObjectRef->getTimelineId());
        
        SpriterTimelineKey *curTimelineKey = (SpriterTimelineKey*)objectTimeline->getKeys()->objectAtIndex(curObjectRef->getTimelineKey());
        SpriterTimelineKey *nextTimelineKey = (SpriterTimelineKey*)objectTimeline->getKeys()->objectAtIndex(nextObjectRef->getTimelineKey());
        
        const char *displayFrameName = ((CCString*)_files->objectForKey(CCString::createWithFormat("%d-%d", curTimelineKey->getFolderId(), curTimelineKey->getFileId())->getCString()))->getCString();
        
        CCSprite *sprite;
        
        if (i >= _spriteNodes->count())
        {
            if (_useBatchNode)
            {
                sprite = CCSprite::createWithSpriteFrameName(displayFrameName);
                _batchNode->addChild(sprite);
            }
            else
            {
                sprite = CCSprite::create(displayFrameName);
                this->addChild(sprite);
            }
            
            _spriteNodes->addObject(sprite);
        }
        else
        {
            sprite = (CCSprite*)_spriteNodes->objectAtIndex(i);
            if (_useBatchNode)
            {
                sprite->setDisplayFrame( CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(displayFrameName));
            }
        }
        
        sprite->setVisible(true);
        
        sprite->setPosition(CCPointMake(
                interpolate(curTimelineKey->getPostion().x, nextTimelineKey->getPostion().x, interpolationFactor),
                interpolate(curTimelineKey->getPostion().y, nextTimelineKey->getPostion().y, interpolationFactor)));
        
        sprite->setAnchorPoint(CCPointMake(
                interpolate(curTimelineKey->getAnchorPoint().x, nextTimelineKey->getAnchorPoint().x, interpolationFactor),
                interpolate(curTimelineKey->getAnchorPoint().y, nextTimelineKey->getAnchorPoint().y, interpolationFactor)));
        
        sprite->setScaleX(interpolate(curTimelineKey->getScaleX(), nextTimelineKey->getScaleX(), interpolationFactor));
        sprite->setScaleY(interpolate(curTimelineKey->getScaleY(), nextTimelineKey->getScaleY(), interpolationFactor));
        
        double nextRotation = nextTimelineKey->getRotation();
        double curRotation = curTimelineKey->getRotation();
        
        if (curTimelineKey->getSpin() == 1 && (nextRotation - curRotation) < 0)
        {
            nextRotation += 360;
        }
        else if(curTimelineKey->getSpin() == -1 && (nextRotation - curRotation ) >0)
        {
            nextRotation -= 360;
        }
        
        // check to flip
        if(_isFlipX)
        {
            // position
            sprite->setPosition(CCPointMake(-sprite->getPosition().x, sprite->getPosition().y));
            
            // scale
            sprite->setScaleX(-sprite->getScaleX());
            
            // rotation
            nextRotation *= -1;
            curRotation *= -1;
        }
        
        sprite->setRotation( - interpolate(curRotation, nextRotation, interpolationFactor) );
    }
}

double SpriterNode::interpolate(double a, double b, double f)
{
    if (f == INFINITY) { f = 0.0; }
    if (f < 0) { f = 0.0; }
    if (f > 1) { f = 1.0; }
    if (f == NAN) { f = 1.0; }
    return a+(b-a)*f;
}

double SpriterNode::getPlaybackSpeed()
{
    return _playbackSpeed;
}

void SpriterNode::setPlaybackSpeed(double pSpeed)
{
    if(pSpeed != _playbackSpeed)
        _playbackSpeed = pSpeed;
}

bool SpriterNode::getIsFlipX()
{
    return _isFlipX;
}

void SpriterNode::setIsFlipX(bool b)
{
    if(b != _isFlipX)
        _isFlipX = b;
}