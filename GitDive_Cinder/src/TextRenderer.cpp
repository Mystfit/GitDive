//
//  TextRenderer.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextRenderer.h"

TextRenderer::TextRenderer(){
    cinder::Font customFont( cinder::Font( "Lucida Console", FONT_SIZE ) );
	cinder::gl::TextureFont::Format f;
	f.enableMipmapping( true );
	m_textureFont = cinder::gl::TextureFont::create( customFont, f );
}



void TextRenderer::makeLineFromFreeElements(boost::shared_ptr<Line> line){

}



void TextRenderer::animLinesIn(vector<boost::shared_ptr<Line> > lines){
    for(vector<boost::shared_ptr<Line> >::iterator it = lines.begin(); it != lines.end(); ++it){
        if(it->get()->getLineState() == Line::LINE_ADDED){
            it->get()->setPosition(cinder::Vec2f(0, it->get()->getLinePos() * LINE_HEIGHT));
            it->get()->animIn(m_timeline, cinder::Vec2f(0, it->get()->getLinePos() * LINE_HEIGHT), cinder::Color(255,255,255));
        } else if(it->get()->getLineState() == Line::LINE_NORMAL){
            it->get()->animIn(m_timeline, cinder::Vec2f(0, it->get()->getLinePos() * LINE_HEIGHT), cinder::Color(255,255,255));
        }
    }
}




void TextRenderer::breakLine(boost::shared_ptr<Line> line){
    vector<LineElement> lineElems = line->getLineElements();
    line->animOut(m_timeline, cinder::Vec2f(0, line->getLinePos() * LINE_HEIGHT), cinder::Color(0,0,0));
    
    for(int i = 0; i < lineElems.size(); i++){
        m_freeLineElements.push_back(lineElems[i]);
    }
    
    line.reset();
}



void TextRenderer::draw(vector< boost::shared_ptr<Line> > & lines){
    
    for(vector< boost::shared_ptr<Line> >::iterator it = lines.begin(); it != lines.end(); ++it){
        
        vector<LineElement> elems = it->get()->getLineElements();
        
        for(int i = 0; i < it->get()->getLineElements().size(); i++){
            elems[i].draw(m_textureFont);
        }
        
        //it->get()->draw(m_textureFont);
    }
}
