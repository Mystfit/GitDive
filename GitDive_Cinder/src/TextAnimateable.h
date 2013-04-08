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

using namespace cinder;

class TextAnimateable {
public:
    TextAnimateable();
    void draw(g::TextureFont & texFont);
    
    virtual std::string getStr();
    
    virtual void animIn( Timeline &timeline, Vec2<float> destVec, Color destColour )
    {
        timeline.apply( &m_colour, destColour, 1.0f, EaseOutAtan( 20 ) );
        timeline.apply( &m_position, destVec, 0.5f, EaseOutAtan( 10 ) ).finishFn( std::bind( &TextAnimateable::onAnimIn, this ) );
    }
    
    virtual void animOut( Timeline &timeline, Vec2<float> destVec, Color destColour )
    {
        timeline.apply( &m_colour, destColour, 1.0f, EaseOutAtan( 20 ) );
        timeline.apply( &m_position, destVec, 0.5f, EaseOutAtan( 10 ) ).finishFn( std::bind( &TextAnimateable::onAnimIn, this ) );    }
    
    virtual void onAnimIn(){
        
    };
    virtual void onAnimOut();

protected:
    Anim<Vec2f> m_position;
    Anim<Color> m_colour;    
};

#endif /* defined(__GitDive_Cinder__TextAnimateable__) */
