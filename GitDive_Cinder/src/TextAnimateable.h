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

class TextAnimateable {
public:
    TextAnimateable();
    void draw(cinder::gl::TextureFont & texFont);
    void animIn( cinder::Timeline &timeline, cinder::Vec2<float> destVec, cinder::Color destColour )
    {
        //timeline.apply( &m_colour, destColour, 1.0f, cinder::easeOutAtan( 20 ) );
        //timeline.apply( &m_position, destVec, 0.5f, cinder::easeOutAtan( 10 ) ).finishFn( std::bind( &TextAnimateable::onAnimIn, this ) );
    }
    
    void animOut( cinder::Timeline &timeline, cinder::Vec2<float> destVec, cinder::Color destColour )
    {
        //timeline.apply( &m_colour, destColour, 1.0f, cinder::easeOutAtan( 20 ) );
        //timeline.apply( &m_position, destVec, 0.5f, cinder::easeOutAtan( 10 ) ).finishFn( std::bind( &TextAnimateable::onAnimIn, this ) );
    }
    
    virtual std::string getStr();
    
//    virtual void onAnimIn();
//    virtual void onAnimOut();
    
private:
    cinder::Anim<cinder::Vec2f> m_position;
    cinder::Anim<cinder::Color> m_colour;
    
};

#endif /* defined(__GitDive_Cinder__TextAnimateable__) */
