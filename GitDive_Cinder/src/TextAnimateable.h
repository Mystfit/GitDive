//
//  TextAnimateable.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#ifndef __GitDive_Cinder__TextAnimateable__
#define __GitDive_Cinder__TextAnimateable__

#define MAX_LIFE 500

#include <iostream>
#include "cinder/Timeline.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Easing.h"
#include "CssParser.h"
#include "TextRenderer.h"

class TextAnimateable {
public:
    TextAnimateable();
    virtual void draw(cinder::gl::TextureFontRef & texFont);
    virtual void update();
    
    //Sets the base colour of an element from the current css theme
    virtual void applyCss(boost::shared_ptr<CssParser> cssParser);
    void applyCss(boost::shared_ptr<CssParser> cssParser, string key);
    
    //Base tweening functions
    virtual void animIn( cinder::TimelineRef, cinder::Vec2<float> destVec, cinder::Color destColour , float duration = 0.5f);
    virtual void animOut( cinder::TimelineRef timeline, cinder::Vec2<float> destVec, cinder::Color destColour, float duration = 1.0f);
    
    //Animation completeion functions
    void onAnimIn();
    void onAnimOut();
    
    //Life accessors
    int getLife(){ return m_life; };
    float getLifePercent(){ return m_life / MAX_LIFE; };
    bool markedForDeletion();
    
    //Attribute getters/setters
    virtual void setPosition(cinder::Vec2f position);
    float getLinePositionFromIndex(int positionIndex){ return (float)positionIndex * FONT_WIDTH; };
    void setColour(cinder::Color colour){m_colour = colour; };
    cinder::Vec2f getPosition(){ return m_position;};
    cinder::Color getColour(){ return m_colour;};
    
    void markAsFreed(){ bIsFree = true; };
    bool isJustFreed();
    
    void markAsCreated(){ bIsCreated = true; };
    bool isJustCreated();
    //String accessor. Returns recursive strings from line elements if present
    virtual std::string getStr();
    
    

protected:
    int m_life;
    bool bIsFree;
    bool bIsCreated;
    
private:
    cinder::Anim<cinder::Vec2f> m_position;
    cinder::Anim<cinder::Color> m_colour;
    cinder::TweenRef<cinder::Vec2f> m_posTween;
    cinder::TweenRef<cinder::Color> m_colourTween;
};

#endif /* defined(__GitDive_Cinder__TextAnimateable__) */
