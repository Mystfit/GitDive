//
//  TextAnimateable.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextAnimateable.h"


                
void TextAnimateable::draw(){
    gl::color( m_colour );
    m_TextureFont->drawString( getStr(), m_postion, 0.0f ) );
    gl::popMatrices();
}
            