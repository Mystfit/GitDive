//
//  TextAnimateable.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextAnimateable.h"
                
void TextAnimateable::draw(TextureFont & texFont){
    gl::color( m_colour );
    texFont->drawString( getStr(), m_position);
}
            