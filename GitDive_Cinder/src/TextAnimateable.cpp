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
    m_textureFont->drawString( getStr(), m_position) ;
}
            