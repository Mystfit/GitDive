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
    //timeline.apply( &m_colour, destColour, 1.0f, cinder::easeOutAtan( 20 ) );
    //timeline.apply( &m_position, destVec, 0.5f, cinder::easeOutAtan( 10 ) ).finishFn( std::bind( &TextAnimateable::onAnimIn, this ) );
}

void TextAnimateable::animOut( cinder::Timeline &timeline, cinder::Vec2<float> destVec, cinder::Color destColour )
{
    //timeline.apply( &m_colour, destColour, 1.0f, cinder::easeOutAtan( 20 ) );
    //timeline.apply( &m_position, destVec, 0.5f, cinder::easeOutAtan( 10 ) ).finishFn( std::bind( &TextAnimateable::onAnimIn, this ) );
}

std::string TextAnimateable::getStr()
{
    
}