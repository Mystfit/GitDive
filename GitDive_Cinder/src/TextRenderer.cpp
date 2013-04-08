//
//  TextRenderer.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextRenderer.h"

TextRenderer::TextRenderer(){
    Font customFont( Font( "Lucidia Console", 100 ) );
	gl::TextureFont::Format f;
	f.enableMipmapping( true );
	mTextureFont = gl::TextureFont::create( customFont, f );
}
