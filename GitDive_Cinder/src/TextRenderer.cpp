//
//  TextRenderer.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextRenderer.h"

TextRenderer::TextRenderer(){
    cinder::Font customFont( cinder::Font( "Lucida Console", 100 ) );
	cinder::gl::TextureFont::Format f;
	f.enableMipmapping( true );
	m_textureFont = cinder::gl::TextureFont::create( customFont, f );
}

void breakLine(boost::shared_ptr<Line> line){
    vector<LineElement> lineElements = line->getLineElements();
    for(vector<LineElement>::iterator it = lineElements.begin(); it != lineElements.end(); ++it){
        m_freeLineElements.push_back(it);
    }
}


void TextRenderer::draw(){
    for(vector< boost::shared_ptr<Line> >::iterator it = m_trackedLines.begin(); it != m_trackedLines.end(); ++it){
        it->get()->draw(m_textureFont);
    }
    
    for(vector<LineElement>::iterator it = m_freeLineElements.begin(); it != m_freeLineElements.end(); ++it){
        it->draw(m_textureFont);
    }
}
