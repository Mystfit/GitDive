//
//  TextRenderer.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextRenderer.h"

TextRenderer::TextRenderer(){
    cinder::Font customFont( Font( "Lucida Console", 100 ) );
	cinder::gl::TextureFont::Format f;
	f.enableMipmapping( true );
	m_textureFont = gl::TextureFont::create( customFont, f );
}
