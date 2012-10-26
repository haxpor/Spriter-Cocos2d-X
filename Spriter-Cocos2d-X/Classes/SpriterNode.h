//
//  SpriterNode.h
//  Tank
//
//  Created by Young Peter on 9/1/12.
//  http://weibo.com/young40
//
//

#ifndef __Tank__SpriterNode__
#define __Tank__SpriterNode__

#include "cocos2d.h"

USING_NS_CC;


class SpriterConfigNode : public CCObject
{
public:
    SpriterConfigNode();
    ~SpriterConfigNode();
    
    static SpriterConfigNode* create(const char* name);
    
    SpriterConfigNode* getParent();
    void setParent(SpriterConfigNode* parent);
    
    const char* getName();
    
    CCArray* getChildren();
    SpriterConfigNode* getChildrenAt(int index);
    int getChildrenCount();
    
    CCDictionary* getProperties();
    CCString* getPropertyCCString(const char* key);
    
private:
    const char *_name;
    SpriterConfigNode *_parent;
    CCArray *_children;
    CCString *_value;
    CCDictionary *_properties;
};

class SpriterObjectRef : public CCObject
{
public:
    int getTimelineId();
    int getTimelineKey();
    void setTimelineId(int timelineId);
    void setTimelineKey(int timelineKey);
    
    static SpriterObjectRef* create();
    
private:
    int _timelineId;
    int _timelineKey;
    
};

class SpriterMainlineKey : public CCObject
{
public:
    CCArray* getObjectRefs();
    void setObjectRefs(CCArray* objectRefs);
    
    static SpriterMainlineKey* create();
    
    void addObjectRef(SpriterObjectRef *objectRef);
    
    double getStartsAt()
    {
        return _startsAt;
    }
    
    void setStartsAt(double start)
    {
        _startsAt = start;
    }
private:
    CCArray *_objectRefs;
    double _startsAt;
};

class SpriterTimelineKey : public CCObject
{
public:
    static SpriterTimelineKey* create();
    
    int getFileId();
    void setFileId(int id);
    
    int getFolderId();
    void setFolderId(int id);
    
    double getStartsAt();
    void setStartsAt(double index);
    
    CCPoint getPostion();
    void setPostion(CCPoint postion);
    
    CCPoint getAnchorPoint();
    void setAnchorPoint(CCPoint anchorPoint);
    
    double getRotation();
    void setRotation(double rotation);
    
    int getSpin();
    void setSpin(int spin);
    
    double getScaleX();
    void setScaleX(double scaleX);
    
    double getScaleY();
    void setScaleY(double scaleY);

private:
    int _file;
    int _folder;
    
    double _startsAt;
    
    CCPoint _position;
    CCPoint _anchorPoint;
    double _rotation;
    int _spin;
    double _scaleX;
    double _scaleY;
};

class SpriterTimeline : public CCObject
{
public:
    static SpriterTimeline* create();
    
    CCArray* getKeys();
    
    void addKeyFrame(SpriterTimelineKey *frame);
    
private:
    CCArray *_keys;    
};

class SpriterAnimation : public CCObject
{
public:
    SpriterAnimation();
    ~SpriterAnimation();
    
    static SpriterAnimation* create();
    
    void addKeyFrame(SpriterMainlineKey *frame);
    void addTimeline(SpriterTimeline *timeline);
    
    CCArray* getMainline();
    CCArray* getTimelines();
    
    const char *getName();
    void setName(const char *name);
    
    double getDuration();
    void setDuration(double duration);
    
private:
    const char *_name;
    CCArray *_mainline;
    CCArray *_timelines;
    double _duration;
    
    int _nodes;
};

class SpriterNode : public CCNode, public CCSAXDelegator
{
public:
    SpriterNode();
    ~SpriterNode();
    
    static SpriterNode* create(const char *scmlFile);
    static SpriterNode* create(const char *scmlFile, const char *imageFile);
    
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);
    
    void runAnimation(const char* animation);
    
    bool getIsFlipX();
    void setIsFlipX(bool b);
    
    /** pSpeed is in percentage, it can be
        1.0 (Normal Speed)
        5.0 (5x speed)
        0.25 (0.25x speed)
        many more
     
        This value can be manually grabbed from Spriter editor, but measure in percentage.
    **/
    double getPlaybackSpeed();
    void setPlaybackSpeed(double pSpeed);
    
private:
    CCString *_characterName;
    
    CCDictionary *_animations;
    CCDictionary *_frames;
    
    CCDictionary *_files;
    
    SpriterAnimation *_curAnimation;
    SpriterMainlineKey *_curKeyFrame;
    SpriterMainlineKey *_nextKeyFrame;
    
    double _duration;
    int _frameIndex;
    
    CCArray *_spriteNodes;
    
    SpriterConfigNode *_configRoot;
    SpriterConfigNode *_curConfigNode;
    
    bool _useBatchNode;
    CCSpriteBatchNode *_batchNode;
    
    void initObjects();
    bool initNodeWithFile(const char *scmlFile);
    void update(float dt);
    double interpolate(double a, double b, double f);
    
    bool _isFlipX;
    double _playbackSpeed;
};


#endif /* defined(__Tank__SpriterNode__) */
