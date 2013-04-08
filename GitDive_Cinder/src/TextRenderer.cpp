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

void TextRenderer::breakLine(boost::shared_ptr<Line> line){
    vector<LineElement> lineElems = line->getLineElements();
    for(int i = 0; i < lineElems.size(); i++){
        m_freeLineElements.push_back(lineElems[i]);
    }
    
    line->reset();
}


void TextRenderer::draw(){
    for(vector< boost::shared_ptr<Line> >::iterator it = m_trackedLines.begin(); it != m_trackedLines.end(); ++it){
        it->get()->draw(m_textureFont);
    }
    
    for(vector<LineElement>::iterator it = m_freeLineElements.begin(); it != m_freeLineElements.end(); ++it){
        it->draw(m_textureFont);
    }
}
