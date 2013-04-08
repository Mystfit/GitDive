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

class TextAnimateable {
public:
    TextAnimateable();
    void draw(cinder::gl::TextureFontRef & texFont);
    void animIn( cinder::TimelineRef, cinder::Vec2<float> destVec, cinder::Color destColour );
    void animOut( cinder::TimelineRef, cinder::Vec2<float> destVec, cinder::Color destColour );
    void setPosition(cinder::Vecf position){ m_position = pos; };
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
