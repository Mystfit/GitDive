//
//  TextAnimateable.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextAnimateable.h"

TextAnimateable::TextAnimateable(){
    
}

                
void TextAnimateable::draw(cinder::gl::TextureFont & texFont){
    cinder::gl::color( m_colour );
    texFont.drawString( getStr(), m_position);
    
}


void TextAnimateable::animIn( cinder::Timeline &timeline, cinder::Vec2<float> destVec, cinder::Color destColour )
{    
    cinder::EaseInAtan easer(20);
    timeline.apply( &m_colour, destColour, 1.0f, easer);
    m_posTween = timeline.apply( &m_position, destVec, 0.5f);
    //timeline.apply( &m_position, destVec, 0.5f).finishFn( std::bind( &TextAnimateable::onAnimIn, this ) );
}

void TextAnimateable::animOut( cinder::Timeline &timeline, cinder::Vec2<float> destVec, cinder::Color destColour )
{
    
    cinder::Tween<cinder::Vec2f> test = timeline.apply(m_position, destVec, 0.5f);
    
    cinder::EaseOutAtan easer(30);
    timeline.apply( &m_colour, destColour, 1.0f,  easer);
    m_posTween = timeline.apply( &m_position, destVec, 0.5f, easer );
}

std::string TextAnimateable::getStr()
{
    return "";
}