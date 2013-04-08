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
    m_colourTween = timeline.apply( &m_colour, destColour, 1.0f,  easer);
    m_posTween = timeline.apply( &m_position, destVec, 0.5f,  easer);
//    timeline.apply( &m_colour, destColour, 1.0f, easer);
//    timeline.apply( &m_position, destVec, 0.5f);
//    timeline.apply( &m_position, destVec, 0.5f).finishFn( std::bind( &TextAnimateable::onAnimIn, this ) );
}

void TextAnimateable::animOut( cinder::Timeline &timeline, cinder::Vec2<float> destVec, cinder::Color destColour )
{
    cinder::EaseOutAtan easer(20);
    m_colourTween = timeline.apply( &m_colour, destColour, 1.0f,  easer);
    m_posTween = timeline.apply( &m_position, destVec, 0.5f,  easer);
    //timeline.apply( &m_colour, destColour, 1.0f,  easer);
    //timeline.apply( &m_position, destVec, 0.5f, cinder::easeOutAtan( 10 ) ).finishFn( std::bind( &TextAnimateable::onAnimIn, this ) );
}

std::string TextAnimateable::getStr()
{
    return "";
}