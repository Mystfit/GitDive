//
//  TextAnimateable.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#ifndef __GitDive_Cinder__TextAnimateable__
#define __GitDive_Cinder__TextAnimateable__

#include <iostream>
#include "cinder/Timeline.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Easing.h"
#include "CssParser.h"

class TextAnimateable {
public:
    TextAnimateable();
    virtual void draw(cinder::gl::TextureFontRef & texFont);
    virtual void update();
    void applyCss(boost::shared_ptr<CssParser> cssparser);
    void animIn( cinder::TimelineRef, cinder::Vec2<float> destVec, cinder::Color destColour , float duration = 0.5f);
    void animOut( cinder::TimelineRef timeline, cinder::Vec2<float> destVec, cinder::Color destColour, float duration = 1.0f);
    void setPosition(cinder::Vec2f position);
    void setColour(cinder::Color colour){m_colour = colour; };
    cinder::Vec2f getPosition(){ return m_position;};
    cinder::Color getColour(){ return m_colour;};
    virtual std::string getStr();
    
    void onAnimIn();
    void onAnimOut();
    
private:
    cinder::Anim<cinder::Vec2f> m_position;
    cinder::Anim<cinder::Color> m_colour;
    cinder::TweenRef<cinder::Vec2f> m_posTween;
    cinder::TweenRef<cinder::Color> m_colourTween;
};

#endif /* defined(__GitDive_Cinder__TextAnimateable__) */
