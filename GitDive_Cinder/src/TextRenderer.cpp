//
//  TextRenderer.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextRenderer.h"

TextRenderer::TextRenderer(){
    cinder::Font customFont( cinder::Font( "GohuFont", FONT_SIZE ) );
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
        //m_freeLineElements.push_back(lineElems[i]);
        //m_freeLineElements.back().setFloating();
    }
    
    line.reset();
}

void TextRenderer::update(){
    
    if(m_targetFile) m_targetFile->update();
    
    for(int i = 0; i < m_freeLineElements.size(); i++){
        //m_freeLineElements[i].draw(m_textureFont);
    }
}



void TextRenderer::draw(){
    
    vector< boost::shared_ptr<Line> > lines;
    
    if(m_targetFile) lines = m_targetFile->getLines();
    else return;
    
    if(lines.size()){
        for(vector< boost::shared_ptr<Line> >::iterator it = lines.begin(); it != lines.end(); ++it){
            
            //Draws the free-floating line elements        
            for(int i = 0; i < m_freeLineElements.size(); i++){
                m_freeLineElements[i].draw(m_textureFont);
            }
            
            it->get()->draw(m_textureFont);
        }
    }
}
