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

using cinder::EaseInAtan, cinder::EaseOutAtan;

class TextAnimateable {
public:
    TextAnimateable();
    void draw(cinder::gl::TextureFont & texFont);
    void animIn( cinder::Timeline &timeline, cinder::Vec2<float> destVec, cinder::Color destColour );
    void animOut( cinder::Timeline &timeline, cinder::Vec2<float> destVec, cinder::Color destColour );
    virtual std::string getStr();
    
    void onAnimIn();
    void onAnimOut();
    
private:
    cinder::Anim<cinder::Vec2f> m_position;
    cinder::Anim<cinder::Color> m_colour;
    
};

#endif /* defined(__GitDive_Cinder__TextAnimateable__) */
